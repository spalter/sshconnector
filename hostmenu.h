/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

===========================================================================
*/

#ifndef __hostmenu_H__
#define __hostmenu_H__

/*
===============================================================================

HostMenu

===============================================================================
*/

#include "string.h"
#include "vector"
#include <ncurses.h>

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
	void			ShowTitle( void );
	void			ShowMenu( void );
	void			CloseDialog( void );

	unsigned int	currentIndex = 0;
	int 			startPosX = 0;
	int 			startPosY = 0;
	int 			screenWidth = 0;
	int 			screenHeight = 0;
	int 			width = 0;
	int 			height = 0;
	WINDOW 			*scrn;
	vector<char*>	items;
};

#endif /* !__hostmenu_H__ */