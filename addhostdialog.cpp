/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

This file is part of sshconnector, distributed under the GNU GPL v2
For full terms see the included COPYING file.

===========================================================================
*/

#include "addhostdialog.h"
#include "sshconnector.h"

/***********************************************************************

AddHostDialog

***********************************************************************/

/*
=====================
AddHostDialog::AddHostDialog
=====================
*/
AddHostDialog::AddHostDialog( void ) {

}

/*
=====================
AddHostDialog::~AddHostDialog
=====================
*/
AddHostDialog::~AddHostDialog( void ) {
	SSHConnector::Log( ( char * ) "Destory AddHostDialog");

    int i;
    for( i = 0; i < 4; i++ ) {
        free_field( fields[i] );
    }	
}

/*
=====================
AddHostDialog::ShowDialog
=====================
*/
int AddHostDialog::ShowDialog( void ) {

	Start();
	int result = Loop();
	Close();

	return result;
}

/*
=====================
AddHostDialog::Start
=====================
*/
void AddHostDialog::Start( void ) {
	/* ncruses stuff */
	clear();
	initscr();									/* Start curses mode 		*/
	cbreak();									/* Line buffering disabled	*/
	keypad( stdscr , true );
	noecho();
	curs_set( 0 );

	CalcualteBounds();

	refresh();

	scrn = newwin( height, width, startPosY, startPosX );
	form = new_form( fields );
	set_form_win( form, scrn );
	set_form_sub( form, derwin( scrn, height - 4, width - 10, 1, 1 ) );
	post_form( form );
}

/*
=====================
AddHostDialog::Initialize
=====================
*/
void AddHostDialog::Initialize( char *file ) {
	filename = file;
	GenerateForm();
}

/*
=====================
AddHostDialog::Loop
=====================
*/
int AddHostDialog::Loop( void ) {
	ShowWindow();

	while( true ) {
		int pressed_key;
		int cols, rows;
		getmaxyx( stdscr, rows, cols );

		if( rows != screenHeight || cols != screenWidth ) {
			Resize();
		}

		pressed_key = wgetch( stdscr );

		switch( pressed_key ) {
			case KEY_DOWN:
				form_driver( form, REQ_NEXT_FIELD );
				form_driver( form, REQ_END_LINE );
				break;
			case KEY_UP:
				form_driver( form, REQ_PREV_FIELD );
				form_driver( form, REQ_END_LINE );
				break;
			case 260:
				form_driver( form, REQ_PREV_CHAR );
				break;
			case 261:
				form_driver( form, REQ_NEXT_CHAR );
				break;
			case 330:
				form_driver( form, REQ_DEL_CHAR );
				break;
			case 263:
				form_driver( form, REQ_DEL_PREV );
				break;
			case 'q': SetStatuslabel( ( char* ) "Quiting..." ); return 0x00;
			default:	
				form_driver( form, pressed_key );
				break;
		}
		
		ShowWindow();
	}
}

/*
=====================
AddHostDialog::ShowWindow
=====================
*/
void AddHostDialog::ShowWindow( void ) {
	box( scrn, 0, 0 );
	
	ShowTitle();
	ShowHintLabel();
	SetStatuslabel( ( char* ) "Add host" );

	mvwprintw( scrn, 1, 2, "Name:" );
	mvwprintw( scrn, 2, 2, "Host:" );
	mvwprintw( scrn, 3, 2, "Port:" );
	mvwprintw( scrn, 4, 2, "User:" );

	wrefresh( scrn );
}

/*
=====================
AddHostDialog::Close
=====================
*/
void AddHostDialog::Close( void ) {
	clear();
	curs_set( 0 );
	echo();
	endwin();			/* End curses mode */

	unpost_form( form );
	free_form( form );
	delwin( scrn );
}

/*
=====================
AddHostDialog::CalcualteBounds
=====================
*/
void AddHostDialog::CalcualteBounds( void ) {
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
AddHostDialog::Resize
=====================
*/
void AddHostDialog::Resize( void ) {
	Close();
	Start();

	ShowWindow();
}

/*
=====================
AddHostDialog::ShowTitle
=====================
*/
void AddHostDialog::ShowTitle( void ) {
	char name[] = "SSHConnector v0.3";
	mvprintw( ( 1 ) , ( screenWidth / 2 ) - ( strlen( name ) / 2 ), name );
}

/*
=====================
AddHostDialog::ShowHintLabel
=====================
*/
void AddHostDialog::ShowHintLabel( void ) {
	mvwprintw( scrn, height - 1, 4, "| [ ]Exit |" );
	mvwaddch( scrn , height - 1, 7, 'q' | A_BOLD );
}

/*
=====================
AddHostDialog::SetStatuslabel
=====================
*/
void AddHostDialog::SetStatuslabel( char *msg ) {
	mvwprintw( scrn, height - 1, width - 8 - strlen( msg ), "| %s |", msg );
}

/*
=====================
AddHostDialog::GenerateMenu
=====================
*/
void AddHostDialog::GenerateForm( void ) {
	SSHConnector::Log( ( char* ) "Generate form" );

	/* Initialize the fields */
	fields[0] = new_field( 1, 40, 0, 8, 0, 0 );
	fields[1] = new_field( 1, 40, 1, 8, 0, 0 );
	fields[2] = new_field( 1, 2, 2, 8, 0, 0 );
	fields[3] = new_field( 1, 20, 3, 8, 0, 0 );
	fields[4] = NULL;

	/* Set field options */
	set_field_back( fields[0], A_UNDERLINE ); 	/* Print a line for the option 	*/
	field_opts_off( fields[0], O_AUTOSKIP );  	/* Don't go to next field when this */
	
	/* Field is filled up */
	set_field_back( fields[1], A_UNDERLINE ); 
	field_opts_off( fields[1], O_AUTOSKIP );

	/* Field is filled up */
	set_field_back( fields[2], A_UNDERLINE ); 
	field_opts_off( fields[2], O_AUTOSKIP );

	/* Field is filled up */
	set_field_back( fields[3], A_UNDERLINE ); 
	field_opts_off( fields[3], O_AUTOSKIP );
}