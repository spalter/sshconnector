/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

This file is part of sshconnector, distributed under the GNU GPL v2
For full terms see the included COPYING file.

===========================================================================
*/

#ifndef __addhostdialog_H__
#define __addhostdialog_H__

/*
===============================================================================

HostMenu

===============================================================================
*/

#include <string>
#include "vector"
#include <ncurses.h>
#include <form.h>

#define KEY_ESCAPE 27
#define KEY_RETURN 10

using namespace std;

class AddHostDialog {
public:
					AddHostDialog( void );
					~AddHostDialog( void );
	int				ShowDialog( void );
	void			Initialize( char *file );
private:
	void			ShowWindow( void );
	void			Resize( void );
	void			Close( void );
	void			Start( void );
	void			CalcualteBounds( void );
	void			ShowTitle( void );
	void			ShowHintLabel( void );
	void			SetStatuslabel( char *msg );
	void			GenerateForm( void );
	int 			Loop ( void );

	char			*filename;
	int 			startPosX 		= 0;
	int 			startPosY 		= 0;
	int 			screenWidth 	= 0;
	int 			screenHeight 	= 0;
	int 			width 			= 0;
	int 			height 			= 0;
	int 			size			= 0;
	WINDOW 			*scrn;
	FORM 			*form;
	FIELD			*fields[5];
};

#endif /* !__addhostdialog_H__ */