/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

This file is part of sshconnector, distributed under the GNU GPL v2
For full terms see the included COPYING file.

===========================================================================
*/

#ifndef __helpdialog_H__
#define __helpdialog_H__

/*
===============================================================================

HostMenu

===============================================================================
*/

#include <string>
#include "vector"
#include <ncurses.h>
#include <menu.h>

#define KEY_ESCAPE 27
#define KEY_RETURN 10

using namespace std;

class HelpDialog {
public:
					HelpDialog( void );
					~HelpDialog( void );
	int				ShowDialog( void );
private:
	void			Initialize( void );
	void			ShowWindow( void );
	void			Resize( void );
	void			Close( void );
	void			Start( void );
	void			CalcualteBounds( void );
	void			ShowTitle( void );
	void			ShowHintLabel( void );
	void			SetStatuslabel( char *msg );
	void			GenerateMenu( vector<char*> &items );
	void			OneStepUp( void );
	void			OneStepDown( void );
	void			PageUp( void );
	void 			PageDown( void );
	int 			Loop ( void );

	char			*filename 		= ( char * ) "manual";
	int 			startPosX 		= 0;
	int 			startPosY 		= 0;
	int 			screenWidth 	= 0;
	int 			screenHeight 	= 0;
	int 			width 			= 0;
	int 			height 			= 0;
	int 			size			= 0;
	WINDOW 			*scrn;
	MENU			*menu;
	ITEM 			**menu_items;
};

#endif /* !__helpdialog_H__ */