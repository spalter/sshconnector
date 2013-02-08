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
#include "helpdialog.h"

using namespace std;

class SSHConnector {
public:
					SSHConnector( void );
					~SSHConnector( void );
	void			Run( void );
	void			Action( char *cmd );
	void			SetHostFile( char *file );
	void			SetUserHostFile( char *file );
	static void		Log( char *msg );

private:
	char			*hostfile;
	char			*userHostFile;
	void			ShowHelp( void );
	void			AddHost( void );
};

#endif /* !__sshconnector_H__ */