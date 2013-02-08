/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

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
HostMenu::HostMenu( char** &items, int size ) {
	int i;
	for( i = 0; i < size ; i++ ) {
		this->items.push_back( items[i] );
	}

	Initialize();
}

/*
=====================
HostMenu::~HostMenu
=====================
*/
HostMenu::~HostMenu( void ) {
	SSHConnector::Log( (char*) "Destory host menu");
}

/*
=====================
HostMenu::ShowDialog
=====================
*/
int HostMenu::ShowDialog( void ) {
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
void HostMenu::CloseDialog( void ) {
	clear();
	curs_set( 1 );
	echo();
	endwin();			/* End curses mode 		*/
	delwin( scrn );
}

/*
=====================
HostMenu::Loop
=====================
*/
int HostMenu::Loop( void ) {
	refresh();

	scrn = newwin( height, width, startPosY, startPosX );
	ShowMenu();

	while( true ) {
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
			case 'q': SetStatuslabel( ( char* ) "Quiting..." ); return 0x271A;
			case 'r': SetStatuslabel( ( char* ) "Refreshing..." ); return 0x2724;
			case 'a': SetStatuslabel( ( char* ) "Add host..." ); return 0x2742;
			case 'h': SetStatuslabel( ( char* ) "Help..." ); return 0x274C;
			case KEY_RETURN: SetStatuslabel( ( char* ) "Connecting..." ); return currentIndex;
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
void HostMenu::Initialize( void ) {
	SSHConnector::Log( (char*) "Initialize host menu");

	/* ncruses stuff */
	clear();
	initscr();											/* Start curses mode 		*/
	cbreak();												/* Line buffering disabled	*/
	keypad( stdscr , true );								/* F1, F2 etc..				*/
	noecho();
	curs_set( 0 );

	/* calculates the screen view */
	Screen();
}

void HostMenu::Screen( void ) {
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
HostMenu::OneStepUp
=====================
*/
void HostMenu::OneStepUp( void ) {
	if( currentIndex == 0 ) {
		currentIndex = items.size() - 1;
	} else {
		--currentIndex;
	}
}

/*
=====================
HostMenu::OneStepDown
=====================
*/
void HostMenu::OneStepDown( void ) {
	if( currentIndex == items.size() - 1 ) {
		currentIndex = 0;
	} else { 
		++currentIndex;
	}
}

/*
=====================
HostMenu::ShowTitle
=====================
*/
void HostMenu::ShowTitle( void ) {
	char name[] = "SSHConnector v0.2";
	mvprintw( ( 1 ) , ( screenWidth / 2 ) - ( strlen( name ) / 2 ), name );
}

/*
=====================
HostMenu::ShowMenu
=====================
*/
void HostMenu::ShowMenu( void ) {
	int x, y;

	x = 2;
	y = 1;

	box( scrn, 0, 0 );

	unsigned int i;
	for( i = 0; i < items.size(); i++ )	{
		if( currentIndex == i ) {
			/* highlight */
			wattron( scrn, A_REVERSE); 
			mvwprintw( scrn, y, x, "%i: %s",i , items[i] );
			wattroff( scrn, A_REVERSE);
		} else {
			/* normal */
			mvwprintw( scrn, y, x, "%i: %s",i , items[i] );
		}

		y++;
	}

	ShowHintLabel();

	if( items.size() > 0) {
		SetStatuslabel( ( char* ) "Ready" );
	} else {
		SetStatuslabel( ( char* ) "No hosts found" );
	}

	wrefresh( scrn );
}

/*
=====================
HostMenu::ShowHintLabel
=====================
*/
void HostMenu::ShowHintLabel( void ) {
	mvwprintw( scrn, height - 1, 4, "| [ ]Exit [ ]Refresh [      ]Select |" );

	mvwaddch( scrn , height - 1, 7, 'q' | A_BOLD );
	mvwaddch( scrn , height - 1, 15, 'r' | A_BOLD );
	mvwaddch( scrn , height - 1, 26, 'R' | A_BOLD );
	mvwaddch( scrn , height - 1, 27, 'e' | A_BOLD );
	mvwaddch( scrn , height - 1, 28, 't' | A_BOLD );
	mvwaddch( scrn , height - 1, 29, 'u' | A_BOLD );
	mvwaddch( scrn , height - 1, 30, 'r' | A_BOLD );
	mvwaddch( scrn , height - 1, 31, 'n' | A_BOLD );
}

/*
=====================
HostMenu::SetStatuslabel
=====================
*/
void HostMenu::SetStatuslabel( char *msg ) {
	mvwprintw( scrn, height - 1, width - 8 - strlen( msg ), "| %s |", msg );
}