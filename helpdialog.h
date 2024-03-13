/*
===========================================================================

SSHConnector
Copyright (C) 2024 Beardman Studios

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
                    HelpDialog();
                    ~HelpDialog();
	int				ShowDialog();
	void			Initialize( char *file );
private:
	void			ShowWindow();
	void			Resize();
	void			Close();
	void			Start();
	void			CalcualteBounds();
	void			ShowTitle();
	void			ShowHintLabel();
	void			SetStatuslabel( char *msg );
	void			GenerateMenu( vector<char*> &items );
	void			OneStepUp();
	void			OneStepDown();
	void			PageUp();
	void 			PageDown();
	int 			Loop ();

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