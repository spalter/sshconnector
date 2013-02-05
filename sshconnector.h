/*
===========================================================================

SSHConnector
Copyright (C) 2013 Spalt3r Development

===========================================================================
*/

#ifndef __sshconnector_H__
#define __sshconnector_H__

/*
===============================================================================

SSHConnector

===============================================================================
*/

#include <stdio.h>
#include <vector>
#include "config.h"
#include "string.h"
#include "hostmenu.h"

using namespace std;

class SSHConnector {
public:
					SSHConnector( void );
					~SSHConnector( void );
	void			Run( void );
	void			Action( char *cmd );
	static void		Log( char *msg );

private:
};

#endif /* !__sshconnector_H__ */