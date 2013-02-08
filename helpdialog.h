/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

===========================================================================
*/

#ifndef __helpdialog_H__
#define __helpdialog_H__

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
	int 			Loop ( void );

	char			*filename 		= ( char * ) "manual";
	int 			startPosX 		= 0;
	int 			startPosY 		= 0;
	int 			screenWidth 	= 0;
	int 			screenHeight 	= 0;
	int 			width 			= 0;
	int 			height 			= 0;
	WINDOW 			*scrn;
	vector<char*> 	items;
};

#endif /* !__helpdialog_H__ */