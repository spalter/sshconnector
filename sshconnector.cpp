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
			int result = 0;

			HostMenu scrn = HostMenu( list, size );
			result = scrn.ShowDialog();

			switch( result ) {
				case 0x271A: exit(0); break;		/* exit */
				case 0x2724: continue; break;		/* refresh */
				default: 
					hosts.GetSshCommandById( cmd, result );
					Action( cmd );
					break;
			}

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