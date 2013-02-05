/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

===========================================================================
*/

#include "config.h"
#include "sshconnector.h"

/***********************************************************************

main

***********************************************************************/

/*
=====================
Config::Config
=====================
*/
Config::Config( void ) {
	
}

/*
=====================
Config::~Config
=====================
*/
Config::~Config( void ) {
	SSHConnector::Log( (char*) "Destroy configuration");
	// Todo: Clean up hosts properly
}

/*
=====================
Config::Initialize
=====================
*/
void Config::Initialize( char *file ) {
	SSHConnector::Log( (char*) "Initialize host configuration" );
	filename = file;
	ReadConfig();
}

/*
=====================
Config::GetHosts
=====================
*/
vector<t_host> Config::GetHosts( void ) {
	return hosts;
}

/*
=====================
Config::ReadConfig
=====================
*/
void Config::ReadConfig( void ) {
	SSHConnector::Log( (char*) "Read configuration" );

	ifstream stream( filename );
	char line[255];

	if(stream) {
	    while( stream ) {
	    	stream.getline( line, 255 );
	    	if( line[0] != '#' && strlen( line ) > 0 ) {
		    	SplitLine( line );
		    }
	    }

		stream.close();
	} else {
		SSHConnector::Log( (char*) "File not found!" );
	}
}

/*
=====================
Config::SplitLine
=====================
*/
void Config::SplitLine( char *line ) {
	const char delimeter = ';';
	char **result;
	
	char *check = (char*) memchr (line, delimeter, strlen(line));
	if (check!=NULL) {
		string string_line;
		string_line.assign( line );

		vector<string> result = Split( string_line, delimeter );
		t_host host = { result[0], result[1], result[2], result[3] };
		hosts.push_back( host );
	}
}

/*
=====================
Config::Split
=====================
*/
vector<string> &Config::Split( const string &str, char delimeter, vector<string> &items ) {
    stringstream str_stream( str );
    string item;

    while( getline( str_stream, item, delimeter ) ) {
        items.push_back( item );
    }

    return items;
}

/*
=====================
Config::Split
=====================
*/
vector<string> Config::Split( const std::string &str, char delimeter ) {
    vector<string> items;
    return Split( str, delimeter, items );
}

/*
=====================
Config::CopyToVectorList
=====================
*/
void Config::CopyToVectorList( vector<char*> &result ) {
	auto list = GetHosts();

	int i;
	for ( i = 0; i < list.size(); i++ ) {
		auto item = BuildHostLine( list[i].name, list[i].host, list[i].port, list[i].user );
		result.push_back( item );
	}
}

/*
=====================
Config::CopyToCharArray
=====================
*/
int Config::CopyToCharArray( char** &result ) {
	auto list = GetHosts();
	result = new char *[list.size()];

	int i;
	for ( i = 0; i < list.size(); i++ ) {
		result[i] = new char [255];
		auto item = BuildHostLine( list[i].name, list[i].host, list[i].port, list[i].user );
		strncpy( result[i], item, strlen( item ) + 1 );
	}

	return i;
}

/*
=====================
Config::ToCharArray
=====================
*/
char *Config::ToCharArray( string &value ) {
	char *out = new char[value.length() + 1];
	strncpy( out, value.c_str(), value.length() + 1 );
	return out;
}

/*
=====================
Config::BuildHostLine
=====================
*/
char *Config::BuildHostLine( string &name, string &host, string &port, string &user ) {
	auto cName = ToCharArray( name );
	auto cHost = ToCharArray( host );
	auto cPort = ToCharArray( port );
	auto cUser = ToCharArray( user );

	char hoststr[250];
	strcpy( hoststr, cName );
	strcat( hoststr, "  ->  " );
	strcat( hoststr, cUser );
	strcat( hoststr, "@" );
	strcat( hoststr, cHost );
	strcat( hoststr, ":" );
	strcat( hoststr, cPort );

	return hoststr;
}

char *Config::GetSshCommandById( int index ) {
	char * item_host = new char[hosts[index].host.length() + 1];
	strncpy( item_host, hosts[index].host.c_str(), hosts[index].host.length() + 1 );

	char * item_port = new char[hosts[index].port.length() + 1];
	strncpy( item_port, hosts[index].port.c_str(), hosts[index].port.length() + 1 );

	char * item_user = new char[hosts[index].user.length() + 1];
	strncpy( item_user, hosts[index].user.c_str(), hosts[index].user.length() + 1 );

	char *sshstr;
	strcpy( sshstr, "ssh " );
	strcat( sshstr, item_host );
	strcat( sshstr, " -p " );
	strcat( sshstr, item_port );
	strcat( sshstr, " -l " );
	strcat( sshstr, item_user );

	return sshstr;
}