/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

===========================================================================
*/

#ifndef __mainscreen_H__
#define __mainscreen_H__

/*
===============================================================================

MainScreen

===============================================================================
*/

#include "config.h"
#include "string.h"
#include <ncurses.h>

#define KEY_ESCAPE 27
#define KEY_ENTER 10

#define WIDTH 30
#define HEIGHT 10 

class MainScreen {
public:
					MainScreen( void );
					~MainScreen( void );
	void			Initialize( void );
	void			Show( void );
	void			Close( void );
	void			Loop( void );
private:
	void 			ShowMenu( WINDOW *wnd );
	void			Action( int choice );

	WINDOW 			*menu;
	int 			highlight = 1;
	int 			choice = 0;
	int 			startPosX = 0;
	int 			startPosY = 0;

	Config 			staticHostConfig;
};

#endif /* !__mainscreen_H__ */