/*
===========================================================================

SSHConnector
Copyright (C) 2014 Spalt3r Development

This file is part of sshconnector, distributed under the GNU GPL v2
For full terms see the included COPYING file.

===========================================================================
*/

#ifndef __aws_H__
#define __aws_H__

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include "json11.hpp"

/*
===============================================================================

AWS

===============================================================================
*/

class AWS {
public:
					AWS();
					~AWS();
auto			GetList() -> std::string;
auto			SetFilter( std::string ) -> void;
private:
auto 			ParseData() -> void;
auto 			RandomString( size_t length ) -> std::string;
auto 			RetriveData() -> void;

std::string user = "";
std::string tmp_file;
std::string tmp_host_file;

std::string CMD_LIST_INSTANCES = "aws ec2 describe-instances --output json --filters 'Name=tag:Name,Values=*%s*' 'Name=instance-state-name,Values=running' > %s";
std::string JSON_RESERVATIONS = "Reservations";
std::string JSON_INSTANCES = "Instances";
std::string JSON_TAGS = "Tags";
std::string JSON_NAME = "Name";
std::string JSON_KEY = "Key";
std::string JSON_VALUE = "Value";
std::string JSON_PUBLICDNSNAME = "PublicDnsName";
std::string TMP_PATH = "/tmp/";
};

#endif /* !__aws_H__ */
