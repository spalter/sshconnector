/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

This file is part of sshconnector, distributed under the GNU GPL v2
For full terms see the included COPYING file.

===========================================================================
*/

#ifndef __hostmenu_H__
#define __hostmenu_H__

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

class HostMenu {
public:
					HostMenu( char** &items, int size );
					~HostMenu( void );
	int				ShowDialog( void );
private:
	int				Loop( void );
	void			Initialize( void );
	void			OneStepUp( void );
	void			OneStepDown( void );
	void			PageUp( void );
	void 			PageDown( void );
	void			ShowTitle( void );
	void			ShowMenu( void );
	void			CloseDialog( void );
	void			ShowHintLabel( void );
	void			SetStatuslabel( char *msg );
	void			Screen( void );
	int			GetItem( void );
	char			*ToCharArray( string &value );

	unsigned int	currentIndex = 0;
	int 			startPosX = 0;
	int 			startPosY = 0;
	int 			screenWidth = 0;
	int 			screenHeight = 0;
	int 			width = 0;
	int 			height = 0;
	int 			size = 0;
	WINDOW 			*scrn;
	MENU			*menu;
	ITEM 			**menu_items;
};

#endif /* !__hostmenu_H__ */