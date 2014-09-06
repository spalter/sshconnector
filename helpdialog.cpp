/*
===========================================================================

SSHConnector
Copyright (C) 2014 Spalt3r Development

This file is part of sshconnector, distributed under the GNU GPL v2
For full terms see the included COPYING file.

===========================================================================
*/

#include "helpdialog.h"
#include "sshconnector.h"

/***********************************************************************

HelpDialog

***********************************************************************/

/*
=====================
HelpDialog::HelpDialog
=====================
*/
HelpDialog::HelpDialog() 
{

}

/*
=====================
HelpDialog::~HelpDialog
=====================
*/
HelpDialog::~HelpDialog() 
{
	SSHConnector::Log( ( char* ) "Destory help dialog");

    int i;
    for ( i = 0; i < size; i++ ) 
    {
        free_item( menu_items[i] );
    }	
}

/*
=====================
HelpDialog::ShowDialog
=====================
*/
int HelpDialog::ShowDialog() 
{
	Start();
	int result = Loop();
	Close();

	return result;
}

/*
=====================
HelpDialog::Start
=====================
*/
void HelpDialog::Start() 
{
	/* ncruses stuff */
	clear();
	initscr();									/* Start curses mode 		*/
	cbreak();									/* Line buffering disabled	*/
	keypad( stdscr , true );					/* F1, F2 etc..				*/
	noecho();
	curs_set( 0 );

	CalcualteBounds();
}

/*
=====================
HelpDialog::Initialize
=====================
*/
void HelpDialog::Initialize( char *file  ) 
{
	SSHConnector::Log( ( char* ) "Read manual" );

	filename = file;
	ifstream stream( filename );
	char line[255];
	vector<char*> items;

	if( stream ) 
	{
	    while ( stream ) 
	    {
	    	stream.getline( line, 255 );
	    	char *out = new char[ strlen(line) + 1];
			strncpy( out, line, strlen(line) + 1 );
	    	items.push_back( out );
	    }

		stream.close();
	} 
	else 
	{
		SSHConnector::Log( ( char* ) "Manual not found!" );
	}

	GenerateMenu( items );
}

/*
=====================
HelpDialog::Loop
=====================
*/
int HelpDialog::Loop() 
{
	refresh();

	scrn = newwin( height, width, startPosY, startPosX );
	menu = new_menu( menu_items );
    set_menu_win( menu, scrn );
    set_menu_sub( menu, derwin( scrn, height - 2, width - 10, 1, 1 ) );
	set_menu_format( menu, height - 2 , 1 );
	set_menu_mark( menu, "" );
	post_menu( menu );

	ShowWindow();

	while ( true ) 
	{
		int pressed_key;
		int cols, rows;
		getmaxyx( stdscr, rows, cols );

		if( rows != screenHeight || cols != screenWidth ) 
		{
			Resize();
		}

		pressed_key = wgetch( stdscr );

		switch( pressed_key ) 
		{
			case KEY_UP: OneStepUp(); break;
			case KEY_DOWN: OneStepDown(); break;
			case KEY_PPAGE: PageUp(); break;
			case KEY_NPAGE: PageDown(); break;
			case 'q': SetStatuslabel( ( char* ) "Quiting..." ); return 0x00;
			default: break;
		}
		
		ShowWindow();
		wrefresh( scrn );
	}
}

/*
=====================
HelpDialog::ShowWindow
=====================
*/
void HelpDialog::ShowWindow() 
{
	box( scrn, 0, 0 );
	
	ShowTitle();
	ShowHintLabel();
	SetStatuslabel( ( char* ) "Help" );
	wrefresh( scrn );
}

/*
=====================
HelpDialog::Close
=====================
*/
void HelpDialog::Close() 
{
	clear();
	curs_set( 1 );
	echo();
	endwin();			/* End curses mode */

	unpost_menu( menu );
	free_menu( menu );
	delwin( scrn );
}

/*
=====================
HelpDialog::CalcualteBounds
=====================
*/
void HelpDialog::CalcualteBounds() 
{
	/* calculates the screen view */
	int spaceH = 20;
	int spaceW = 10;

	getmaxyx( stdscr, screenHeight, screenWidth );		/* get the boundaries of the screeen */

	width = screenWidth - ( screenWidth * spaceW / 100 );
	height = screenHeight - ( screenHeight * spaceH / 100 );

	startPosY = ( screenHeight - height ) / 2 + 1;
	startPosX = ( screenWidth - width ) / 2;
}

/*
=====================
HelpDialog::Resize
=====================
*/
void HelpDialog::Resize() 
{
	Close();
	Start();
	refresh();

	scrn = newwin( height, width, startPosY, startPosX );
	menu = new_menu( menu_items );
    set_menu_win( menu, scrn );
    set_menu_sub( menu, derwin( scrn, height - 2, width - 10, 1, 1 ) );
	set_menu_format( menu, height - 2 , 1 );
	set_menu_mark( menu, "" );
	post_menu( menu );

	ShowWindow();
	wrefresh( scrn );
}

/*
=====================
HelpDialog::ShowTitle
=====================
*/
void HelpDialog::ShowTitle() 
{
	char name[] = "SSHConnector v0.3";
	mvprintw( ( 1 ) , ( screenWidth / 2 ) - ( strlen( name ) / 2 ), name );
}

/*
=====================
HelpDialog::ShowHintLabel
=====================
*/
void HelpDialog::ShowHintLabel() 
{
	mvwprintw( scrn, height - 1, 4, "| [ ]Exit |" );
	mvwaddch( scrn , height - 1, 7, 'q' | A_BOLD );
}

/*
=====================
HelpDialog::SetStatuslabel
=====================
*/
void HelpDialog::SetStatuslabel( char *msg ) 
{
	mvwprintw( scrn, height - 1, width - 8 - strlen( msg ), "| %s |", msg );
}

/*
=====================
HelpDialog::GenerateMenu
=====================
*/
void HelpDialog::GenerateMenu( vector<char*> &items ) 
{
	int i;
	this->size = items.size();
	menu_items = ( ITEM ** ) calloc ( size + 1, sizeof( ITEM * ) );
	for ( i = 0; i < size ; i++ ) {
		menu_items[i] = new_item( "# ", items[i] );
	}
}

/*
=====================
HelpDialog::OneStepUp
=====================
*/
void HelpDialog::OneStepUp() 
{
	menu_driver( menu, REQ_UP_ITEM );
}

/*
=====================
HelpDialog::OneStepDown
=====================
*/
void HelpDialog::OneStepDown() 
{
	menu_driver( menu, REQ_DOWN_ITEM );
}

/*
=====================
HelpDialog::PageUp
=====================
*/
void HelpDialog::PageUp() 
{
	menu_driver( menu, REQ_SCR_UPAGE );
}

/*
=====================
HelpDialog::PageDown
=====================
*/
void HelpDialog::PageDown() 
{
	menu_driver( menu, REQ_SCR_DPAGE );
}