/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

===========================================================================
*/

#include "mainscreen.h"
#include "sshconnector.h"

/***********************************************************************

MainScreen

***********************************************************************/

/*
=====================
MainScreen::MainScreen
=====================
*/
MainScreen::MainScreen( void ) {

}

/*
=====================
MainScreen::~MainScreen
=====================
*/
MainScreen::~MainScreen( void ) {

}

/*
=====================
MainScreen::Initialize
=====================
*/
void MainScreen::Initialize( void ) {
	SSHConnector::Log( "Initialize main screen" );

	staticHostConfig = Config();
	staticHostConfig.Initialize( "hosts.conf" );

	// Ncurses init
	initscr();
	clear();
	noecho();
	cbreak();

	startPosX = (80 - WIDTH) / 2;
	startPosY = (24 - HEIGHT) / 2;

	menu = newwin(HEIGHT, WIDTH, startPosY, startPosX);
	keypad(menu, TRUE);
	mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	mvprintw(10, 20, "SSHConnector");
	mvprintw(12, 20, "Spalt3r Development");
	refresh();
	ShowMenu( menu );
}

/*
=====================
MainScreen::Show
=====================
*/
void MainScreen::Show( void ) {
	SSHConnector::Log( "Show main screen" );
	Loop();
}

/*
=====================
MainScreen::Close
=====================
*/
void MainScreen::Close( void ) {
	SSHConnector::Log( "Close window" );

	clrtoeol();
	refresh();
	endwin();
}

/*
=====================
MainScreen::Loop
=====================
*/
void MainScreen::Loop( void ) {
	SSHConnector::Log( "Run loop" );

	int pressed_char;
	while(1)
	{	
		pressed_char = wgetch( menu );
		switch( pressed_char )
		{	case KEY_UP:
				if(highlight == 1)
					highlight = staticHostConfig.GetHosts().size();
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == staticHostConfig.GetHosts().size())
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				Action( choice );
				break;
			default:
				refresh();
				break;
		}
		ShowMenu( menu );
	}
}

/*
=====================
MainScreen::ShowMenu
=====================
*/
void MainScreen::ShowMenu( WINDOW *wnd ) {
	auto hosts = staticHostConfig.GetHosts();
	int pos_x, pos_y, i;

	pos_x = 2;
	pos_y = 2;
	box(wnd, 0, 0);
	for(i = 0; i < hosts.size(); ++i)
	{	
		char * item_name = new char[hosts[i].name.length() + 1];
		strncpy( item_name, hosts[i].name.c_str(), hosts[i].name.length() + 1 );

		if(highlight == i + 1) /* High light the present choice */
		{	
			wattron(wnd, A_REVERSE); 
			mvwprintw(wnd, pos_y, pos_x, "Host: %s", item_name);
			wattroff(wnd, A_REVERSE);
		} else {
			mvwprintw(wnd, pos_y, pos_x, "Host: %s", item_name);
		}
		++pos_y;
	}

	wrefresh(wnd);
}

/*
=====================
MainScreen::Action
=====================
*/
void MainScreen::Action( int i ) {
	auto hosts = staticHostConfig.GetHosts();
	char * item_host = new char[hosts[i].host.length() + 1];
	strncpy( item_host, hosts[i].host.c_str(), hosts[i].host.length() + 1 );

	char * item_port = new char[hosts[i].port.length() + 1];
	strncpy( item_port, hosts[i].port.c_str(), hosts[i].port.length() + 1 );

	char * item_user = new char[hosts[i].user.length() + 1];
	strncpy( item_user, hosts[i].user.c_str(), hosts[i].user.length() + 1 );

	char sshstr[250];
	strcpy( sshstr, "ssh " );
	strcat( sshstr, item_host );
	strcat( sshstr, " -p " );
	strcat( sshstr, item_port );
	strcat( sshstr, " -l " );
	strcat( sshstr, item_user );

	system( "clear" );
	system( sshstr );
}