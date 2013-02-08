/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

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
HelpDialog::HelpDialog( void ) {
	Initialize();
}

/*
=====================
HelpDialog::~HelpDialog
=====================
*/
HelpDialog::~HelpDialog( void ) {
	SSHConnector::Log( (char*) "Destory help dialog");
}

/*
=====================
HelpDialog::ShowDialog
=====================
*/
int HelpDialog::ShowDialog( void ) {
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
void HelpDialog::Start( void ) {
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
void HelpDialog::Initialize( void ) {
	SSHConnector::Log( (char*) "Read manual" );

	ifstream stream( filename );
	char line[255];

	if( stream ) {
	    while( stream ) {
	    	stream.getline( line, 255 );
	    	char *out = new char[ strlen(line) + 1];
			strncpy( out, line, strlen(line) + 1 );
	    	items.push_back( out );
	    }

		stream.close();
	} else {
		SSHConnector::Log( (char*) "Manual not found!" );
	}
}

/*
=====================
HelpDialog::Loop
=====================
*/
int HelpDialog::Loop( void ) {
	refresh();

	scrn = newwin( height, width, startPosY, startPosX );
	ShowWindow();

	while( true ) {
		int pressed_key;
		int cols, rows;
		getmaxyx( stdscr, rows, cols );

		if( rows != screenHeight || cols != screenWidth ) {
			Resize();
		}

		pressed_key = wgetch( stdscr );

		if ( pressed_key == 'q' ) {
			return 0x00;
		}
		
		ShowWindow();
	}
}

/*
=====================
HelpDialog::ShowWindow
=====================
*/
void HelpDialog::ShowWindow( void ) {
	int x, y;

	x = 2;
	y = 1;

	box( scrn, 0, 0 );

	unsigned int i;
	for( i = 0; i < items.size(); i++ ) {
		mvwprintw( scrn, y, x, items[i] );
		y++;
	}

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
void HelpDialog::Close( void ) {
	clear();
	curs_set( 1 );
	echo();
	endwin();			/* End curses mode */
	delwin( scrn );
}

/*
=====================
HelpDialog::CalcualteBounds
=====================
*/
void HelpDialog::CalcualteBounds( void ) {
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
void HelpDialog::Resize( void ) {
	Close();
	Start();
	refresh();
	scrn = newwin( height, width, startPosY, startPosX );
	ShowWindow();
	wrefresh( scrn );
}

/*
=====================
HelpDialog::ShowTitle
=====================
*/
void HelpDialog::ShowTitle( void ) {
	char name[] = "SSHConnector v0.2";
	mvprintw( ( 1 ) , ( screenWidth / 2 ) - ( strlen( name ) / 2 ), name );
}

/*
=====================
HelpDialog::ShowHintLabel
=====================
*/
void HelpDialog::ShowHintLabel( void ) {
	mvwprintw( scrn, height - 1, 4, "| [ ]Exit |" );
	mvwaddch( scrn , height - 1, 7, 'q' | A_BOLD );
}

/*
=====================
HelpDialog::SetStatuslabel
=====================
*/
void HelpDialog::SetStatuslabel( char *msg ) {
	mvwprintw( scrn, height - 1, width - 8 - strlen( msg ), "| %s |", msg );
}