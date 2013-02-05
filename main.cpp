/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

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
	
	app.Run();
}