/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

This file is part of sshconnector, distributed under the GNU GPL v2
For full terms see the included COPYING file.

===========================================================================
*/

#include "main.h"
#include <stdio.h>

using namespace std;
/***********************************************************************

main

***********************************************************************/

/*
=====================
main
=====================
*/
int main( int argc, char** argv ) {
	auto app = SSHConnector();

	if ( argc > 1 ) {
		app.SetHostFile( argv[1] );
	}

	if ( argc > 2 ) {
		app.SetUserHostFile( argv[2] );
	}

	if ( argc > 3 ) {
		app.SetHelpFile( argv[3] );
	}
	
	app.Run();
}