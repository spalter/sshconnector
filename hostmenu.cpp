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
	curs_set(1);
	echo();
	endwin();			/* End curses mode 		*/
}

/*
=====================
HostMenu::Loop
=====================
*/
int HostMenu::Loop( void ) {
	int pressed_key;

	refresh();
	scrn = newwin( height, width, startPosY, startPosX );
	ShowMenu();

	while( true ) {
		pressed_key = wgetch( stdscr );
		switch( pressed_key ) {
			case KEY_UP: OneStepUp(); break;
			case KEY_DOWN: OneStepDown(); break;
			case 'q': return 0x271A;
			case 'r': return 0x2724;
			case KEY_RETURN: return currentIndex;
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
	initscr();											/* Start curses mode 		*/
	cbreak();												/* Line buffering disabled	*/
	keypad( stdscr , true);								/* F1, F2 etc..				*/
	noecho();
	curs_set(0);

	/* calculates the screen view */
	int spaceH = 20;
	int spaceW = 10;

	getmaxyx(stdscr, screenHeight, screenWidth);		/* get the boundaries of the screeen */

	width = screenWidth - (screenWidth * spaceW / 100);
	height = screenHeight - (screenHeight * spaceH / 100);

	startPosY = (screenHeight - height) / 2 + 1;
	startPosX = (screenWidth - width) / 2;
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
	if( currentIndex == items.size() ) {
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
	char name[] = "SSHConnector";
	char author[] = "by Spalt3r Development";
	mvprintw( (1 ) , (screenWidth / 2) - ( strlen( name ) / 2 ), name );
	mvprintw( (2 ) , (screenWidth / 2) - ( strlen( author ) / 2 ), author );
}

/*
=====================
HostMenu::ShowMenu
=====================
*/
void HostMenu::ShowMenu( void ) {
	int x, y;

	x = 2;
	y = 2;

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

	mvwprintw( scrn, height - 1, 4, " [q]Exit [r]Refresh [Return]Select " );
	wrefresh( scrn );
}