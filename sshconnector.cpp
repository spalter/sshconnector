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
		hosts.Initialize( "hosts.conf" );
		{
			char** list;
			int size = hosts.CopyToCharArray( list );

			HostMenu scrn = HostMenu( list, size );
			Action( hosts.GetSshCommandById( scrn.ShowDialog() ) );
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