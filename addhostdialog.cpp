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
	SSHConnector::Log( ( char* ) "Build add host dialog");
}

/*
=====================
AddHostDialog::~AddHostDialog
=====================
*/
AddHostDialog::~AddHostDialog( void ) {
	SSHConnector::Log( ( char* ) "Destory add host dialog");
}

/*
=====================
AddHostDialog::ShowDialog
=====================
*/
int AddHostDialog::ShowDialog( void ) {
	EnableNcurses();
	int result = Loop();
	DisableNcurses();

	return result;
}

/*
=====================
AddHostDialog::SetWindowBounds
=====================
*/
void AddHostDialog::SetWindowBounds( void ) {
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
AddHostDialog::EnableNcurses
=====================
*/
void AddHostDialog::EnableNcurses( void ) {
	/* ncruses stuff */
	clear();
	initscr();									/* Start curses mode 		*/
	cbreak();									/* Line buffering disabled	*/
	keypad( stdscr , true );					/* F1, F2 etc..				*/
	noecho();
	curs_set( 0 );

	SetWindowBounds();
	scrn = newwin( height, width, startPosY, startPosX );	
}

/*
=====================
AddHostDialog::DisableNcurses
=====================
*/
void AddHostDialog::DisableNcurses( void ) {
	clear();
	curs_set( 1 );
	echo();
	endwin();			/* End curses mode */

	unpost_form( form );
	free_form( form );
	free_field( fields[0] );
	free_field( fields[1] );

	delwin( scrn );
}

/*
=====================
AddHostDialog::Loop
=====================
*/
int AddHostDialog::Loop (void ) {
	refresh();
	GenerateForm();
	ShowForm();
	int pressed_key;
	
	while( true )
	{	
		pressed_key = getch();
		switch( pressed_key )
		{	case KEY_DOWN:
				form_driver( form, REQ_NEXT_FIELD );
				form_driver( form, REQ_END_LINE );
				break;
			case KEY_UP:
				form_driver( form, REQ_PREV_FIELD );
				form_driver( form, REQ_END_LINE );
				break;
			case 'q': return 0;
			default:	
				form_driver( form, pressed_key );
				break;
		}

		ShowForm();
	}
	return 0;
}

/*
=====================
AddHostDialog::ShowForm
=====================
*/
void AddHostDialog::ShowForm( void ) {
	box( scrn, 0, 0 );

	ShowTitle();
	ShowHintLabel();
	SetStatuslabel( ( char* ) "Add host" );
	wrefresh( scrn );
}

/*
=====================
AddHostDialog::GenerateForm
=====================
*/
void AddHostDialog::GenerateForm( void ) {
	/* Initialize the fields */
	fields[0] = new_field( 1, 10, 4, 18, 0, 0 );
	fields[1] = new_field( 1, 10, 6, 18, 0, 0 );
	fields[2] = NULL;

	/* Set field options */
	set_field_back( fields[0], A_UNDERLINE ); 	/* Print a line for the option 	*/
	field_opts_off( fields[0], O_AUTOSKIP );  	/* Don't go to next field when this */
	
	/* Field is filled up */
	set_field_back( fields[1], A_UNDERLINE ); 
	field_opts_off( fields[1], O_AUTOSKIP );

	/* Create the form and post it */
	form = new_form( fields );
	set_form_win( form, scrn );
	post_form( form );
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