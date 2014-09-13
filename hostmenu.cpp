/*
===========================================================================

SSHConnector
Copyright (C) 2014 Spalt3r Development

This file is part of sshconnector, distributed under the GNU GPL v2
For full terms see the included COPYING file.

===========================================================================
*/

#include "hostmenu.h"
#include "sshconnector.h"

/***********************************************************************

HostMenu

***********************************************************************/

/*
=====================
HostMenu::HostMenu
=====================
*/
HostMenu::HostMenu( char** &items, int size ) 
{	
	this->size = size;
	menu_items = ( ITEM ** ) calloc ( this->size + 1, sizeof( ITEM * ) );
	
	for ( int i = 0; i < this->size ; i++ ) 
	{
		string str = to_string( i );
		str.append(": ");
		char *host = ToCharArray( str );
		menu_items[i] = new_item( host, items[i] );
	}

	Initialize();
}

/*
=====================
HostMenu::~HostMenu
=====================
*/
HostMenu::~HostMenu() 
{
	SSHConnector::Log( ( char* ) "Destory host menu");
}

/*
=====================
HostMenu::ToCharArray
=====================
*/
char *HostMenu::ToCharArray( string &value ) 
{
	char *out = new char[value.length() + 1];
	strncpy( out, value.c_str(), value.length() + 1 );
	return out;
}

/*
=====================
HostMenu::ShowDialog
=====================
*/
int HostMenu::ShowDialog() 
{
	ShowTitle();
	int result = Loop();
	CloseDialog();
	return result;
}

/*
=====================
HostMenu::CloseDialog
=====================
*/
void HostMenu::CloseDialog() 
{
	clear();
	curs_set( 1 );
	echo();
	endwin();			/* End ncurses mode */
	
	unpost_menu( menu );
    free_menu( menu );

    for ( int i = 0; i < size; i++ ) 
    {
        free_item( menu_items[i] );
    }

	delwin( scrn );
}

/*
=====================
HostMenu::Loop
=====================
*/
int HostMenu::Loop() 
{
	refresh();

	scrn = newwin( height, width, startPosY, startPosX );

	menu = new_menu( menu_items );
    set_menu_win( menu, scrn );
    set_menu_sub( menu, derwin( scrn, height - 4, width - 10, 2, 1 ) );
	set_menu_format( menu, height - 4 , 1 );
	set_menu_mark( menu, " * " );
	post_menu( menu );

	if( size == 0 ) 
	{
		SetStatuslabel( ( char* ) "No hosts found" );
	}

	ShowMenu();

	while ( true ) 
	{
		int pressed_key;
		int cols, rows;
		getmaxyx( stdscr, rows, cols );

		if( rows != screenHeight || cols != screenWidth ) {
			return 0x272E;
		}

		pressed_key = wgetch( stdscr );

		switch( pressed_key ) {
			case KEY_UP: OneStepUp(); break;
			case KEY_DOWN: OneStepDown(); break;
			case KEY_PPAGE: PageUp(); break;
			case KEY_NPAGE: PageDown(); break;
			case 'q': SetStatuslabel( ( char* ) "Quiting..." ); return 0x271A;
			case 'r': SetStatuslabel( ( char* ) "Refreshing..." ); return 0x2724;
			case 'h': SetStatuslabel( ( char* ) "Help..." ); return 0x274C;
			case KEY_RETURN: SetStatuslabel( ( char* ) "Connecting..." ); return GetItem();
			default: refresh(); break;
		}

		ShowMenu();
	}
}

/*
=====================
HostMenu::Initialize
=====================
*/
void HostMenu::Initialize() 
{
	SSHConnector::Log( ( char* ) "Initialize host menu");

	/* ncruses stuff */
	clear();
	initscr();												/* Start curses mode 		*/
	cbreak();												/* Line buffering disabled	*/
	keypad( stdscr , true );								/* F1, F2 etc..				*/
	noecho();
	curs_set( 0 );

	/* calculates the screen view */
	Screen();
}

void HostMenu::Screen() 
{
	/* calculates the screen view */
	int spaceH = 15;
	int spaceW = 10;

	getmaxyx( stdscr, screenHeight, screenWidth );		/* get the bounds of the screeen */

	width = screenWidth - ( screenWidth * spaceW / 100 );
	height = screenHeight - ( screenHeight * spaceH / 100 );

	startPosY = ( screenHeight - height ) / 2 + 1;
	startPosX = ( screenWidth - width ) / 2;
}

/*
=====================
HostMenu::OneStepUp
=====================
*/
void HostMenu::OneStepUp() 
{
	menu_driver( menu, REQ_UP_ITEM );
}

/*
=====================
HostMenu::OneStepDown
=====================
*/
void HostMenu::OneStepDown() 
{
	menu_driver( menu, REQ_DOWN_ITEM );
}

/*
=====================
HostMenu::PageUp
=====================
*/
void HostMenu::PageUp() 
{
	menu_driver( menu, REQ_SCR_UPAGE );
}

/*
=====================
HostMenu::PageDown
=====================
*/
void HostMenu::PageDown() 
{
	menu_driver( menu, REQ_SCR_DPAGE );
}

/*
=====================
HostMenu::ShowTitle
=====================
*/
void HostMenu::ShowTitle() 
{
	char name[] = "SSHConnector v0.4";
	mvprintw( ( 1 ) , ( screenWidth / 2 ) - ( strlen( name ) / 2 ), name );
}

/*
=====================
HostMenu::ShowMenu
=====================
*/
void HostMenu::ShowMenu() 
{
	box( scrn, 0, 0 );

	ShowHintLabel();

	if( size > 0 ) 
	{
		SetStatuslabel( ( char* ) "Ready" );
	} 
	else 
	{
		SetStatuslabel( ( char* ) "No hosts found" );
	}

	wrefresh( scrn );
}

/*
=====================
HostMenu::ShowHintLabel
=====================
*/
void HostMenu::ShowHintLabel() 
{
	mvwprintw( scrn, height - 1, 4, "| [ ]Exit [ ]Refresh [      ]Select [ ]Help |" );

	mvwaddch( scrn , height - 1, 7, 'q' | A_BOLD );
	mvwaddch( scrn , height - 1, 15, 'r' | A_BOLD );
	mvwaddch( scrn , height - 1, 26, 'R' | A_BOLD );
	mvwaddch( scrn , height - 1, 27, 'e' | A_BOLD );
	mvwaddch( scrn , height - 1, 28, 't' | A_BOLD );
	mvwaddch( scrn , height - 1, 29, 'u' | A_BOLD );
	mvwaddch( scrn , height - 1, 30, 'r' | A_BOLD );
	mvwaddch( scrn , height - 1, 31, 'n' | A_BOLD );
	mvwaddch( scrn , height - 1, 41, 'h' | A_BOLD );
}

/*
=====================
HostMenu::SetStatuslabel
=====================
*/
void HostMenu::SetStatuslabel( char *msg ) 
{
	mvwprintw( scrn, height - 1, width - 8 - strlen( msg ), "| %s |", msg );
}

/*
=====================
HostMenu::GetItem
=====================
*/
int HostMenu::GetItem() 
{
	return item_index( current_item( menu ) );
}