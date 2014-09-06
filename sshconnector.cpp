/*
===========================================================================

SSHConnector
Copyright (C) 2014 Spalt3r Development

This file is part of sshconnector, distributed under the GNU GPL v2
For full terms see the included COPYING file.

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
SSHConnector::SSHConnector() 
{

}

/*
=====================
SSHConnector::~SSHConnector
=====================
*/
SSHConnector::~SSHConnector() 
{

}

/*
=====================
SSHConnector::Run
=====================
*/
void SSHConnector::Run() 
{
	while ( true ) 
	{
		/* App stuff */
		auto hosts = Config();

		hosts.Initialize( hostfile );
		if(strlen( userHostFile ) > 0 ) 
		{
			hosts.AppendList( userHostFile );
		}

		char** list;
		char *cmd = new char[255];
		int size = hosts.CopyToCharArray( list );
		int result = 0;

		HostMenu scrn = HostMenu( list, size );
		result = scrn.ShowDialog();

		switch( result ) 
		{
			case 0x271A: system( "clear" ); exit( 0x00 ); break;		/* exit */
			case 0x2724: continue; break;								/* refresh */
			case 0x272E: break; 										/* resize windows */
			case 0x274C: ShowHelp(); break;								/* show help */
			default:
				if( size > 0x00 ) 
				{
					hosts.GetSshCommandById( cmd, result );
					Action( cmd );
				}
				break;
		}

		delete cmd;
		delete list;
	}
}

/*
=====================
SSHConnector::Log
=====================
*/
void SSHConnector::Log( char *msg ) 
{
	// printf( "Log Message: %s\n", msg );
}

/*
=====================
SSHConnector::Action
=====================
*/
void SSHConnector::Action( char *cmd ) 
{
	system ( "clear" );
	system ( "echo Connecting to server..." );
	system ( cmd );
}

/*
=====================
SSHConnector::SetHostFile
=====================
*/
void SSHConnector::SetHostFile( char *file ) 
{
	hostfile = file;
}

/*
=====================
SSHConnector::SetUserHostFile
=====================
*/
void SSHConnector::SetUserHostFile( char *file ) 
{
	userHostFile = file;
}

/*
=====================
SSHConnector::SetHelpFile
=====================
*/
void SSHConnector::SetHelpFile( char *file ) 
{
	helpFile = file;
}

/*
=====================
SSHConnector::ShowHelp
=====================
*/
void SSHConnector::ShowHelp() 
{
	auto help = HelpDialog();
	help.Initialize( helpFile );
	help.ShowDialog();
}