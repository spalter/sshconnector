/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

===========================================================================
*/

#include "sshconnector.h"

/***********************************************************************

SSHConnector

***********************************************************************/

/*
=====================
SSHConnector::SSHConnector
=====================
*/
SSHConnector::SSHConnector( void ) {

}

/*
=====================
SSHConnector::~SSHConnector
=====================
*/
SSHConnector::~SSHConnector( void ) {

}

/*
=====================
SSHConnector::Run
=====================
*/
void SSHConnector::Run( void ) {
	while (true) {
		auto hosts = Config();
		hosts.Initialize( (char*) "hosts.conf" );
		{
			char** list;
			char *cmd = new char[255];
			int size = hosts.CopyToCharArray( list );

			HostMenu scrn = HostMenu( list, size );
			hosts.GetSshCommandById( cmd, scrn.ShowDialog() );
			Action( cmd );

			delete cmd;
			delete list;
		}
	}
}

/*
=====================
SSHConnector::Log
=====================
*/
void SSHConnector::Log( char *msg ) {
	// printf( "Log Message: %s\n", msg );
}

void SSHConnector::Action( char *cmd ) {
	system ( "clear" );
	system ( cmd );
}