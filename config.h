/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

This file is part of sshconnector, distributed under the GNU GPL v2
For full terms see the included COPYING file.

===========================================================================
*/

#ifndef __config_H__
#define __config_H__

/*
===============================================================================

config

===============================================================================
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <sstream>

using namespace std;

typedef struct t_host {
	string name;
	string host;
	string port;
	string user;
} t_host;

class Config {
public:
					Config();
					~Config();
	void 			Initialize( char *file );
	void			AppendList( char *file );
	void			CopyToVectorList( vector<char*> &result );
	void			GetSshCommandById( char *cmd, int index );
	int				CopyToCharArray( char** &result );
	vector<t_host> 	GetHosts();
private:
	void 			ReadConfig();
	void 			SplitLine( char *line );
	vector<string> 	&Split( const string &str, char delimeter, vector<string> &items );
	vector<string>	Split( const string &str, char delimeter );
	char			*ToCharArray( string &value );
	void 			BuildHostLine( char *line, string &name, string &host, string &port, string &user );

	char			*filename;
	vector<t_host> 	hosts;
};

#endif /* !__config_H__ */