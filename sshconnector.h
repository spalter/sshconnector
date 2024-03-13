/*
===========================================================================

SSHConnector
Copyright (C) 2024 Beardman Studios

This file is part of sshconnector, distributed under the GNU GPL v2
For full terms see the included COPYING file.

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
                    SSHConnector();
                    ~SSHConnector();
	void			Run();
	void			Action( char *cmd );
	void			SetHostFile( char *file );
	void			SetUserHostFile( char *file );
	void			SetHelpFile( char *file );
	static void		Log( char *msg );

private:
	char			*hostfile;
	char			*userHostFile;
	char			*helpFile;
	void			ShowHelp();
};

#endif /* !__sshconnector_H__ */