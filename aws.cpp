/*
===========================================================================

SSHConnector
Copyright (C) 2014 Spalt3r Development

This file is part of sshconnector, distributed under the GNU GPL v2
For full terms see the included COPYING file.

===========================================================================
*/

#include "aws.h"

/***********************************************************************

SSHConnector

***********************************************************************/

/*
=====================
AWS:AWS:
=====================
*/
AWS::AWS()
{

}

/*
=====================
AWS::AWS~
=====================
*/
AWS::~AWS()
{
	remove( tmp_file.c_str() );
	remove( tmp_host_file.c_str() );
}

/*
=====================
AWS::SetFilter
=====================
*/
void AWS::SetFilter( std::string filter )
{
	user = filter;
}

/*
=====================
AWS::GetList
=====================
*/
std::string AWS::GetList()
{
	RetriveData();
	ParseData();
	return tmp_host_file;
}

/*
=====================
AWS::RetriveData
=====================
*/
void AWS::RetriveData()
{
  tmp_file = TMP_PATH + RandomString( 10 ) + ".x";
  tmp_host_file = TMP_PATH + RandomString( 10 ) + ".x";
  char* cmd = new char[CMD_LIST_INSTANCES.length() + user.length() + tmp_file.length() + 32];

  sprintf( cmd, CMD_LIST_INSTANCES.c_str(), user.c_str(), tmp_file.c_str() );
  system( cmd );

  delete[] cmd;
}

/*
=====================
AWS::ParseData
=====================
*/
void AWS::ParseData()
{
  std::ifstream ifs( tmp_file );
  std::string content( ( std::istreambuf_iterator<char>( ifs ) ),
                       ( std::istreambuf_iterator<char>() ) );

  std::string err;
  auto json = json11::Json::parse( content, err );
  if (!err.empty()) {
     printf("Failed: %s\n", err.c_str());
  } else {

		std::ofstream host_file;
  	host_file.open( tmp_host_file );

    for( auto &reservations: json[JSON_RESERVATIONS].array_items() )
    {
      for( auto &instance: reservations[JSON_INSTANCES].array_items() )
      {
        std::string name;
        for( auto &tag: instance[JSON_TAGS].array_items() )
        {
          if( tag[JSON_KEY].string_value() == JSON_NAME )
          {
            name = tag[JSON_VALUE].string_value();
          }
        }

				host_file << name << ";" << instance[JSON_PUBLICDNSNAME].string_value() << ";22;root" << std::endl;
      }
    }

		host_file.close();
  }
}

/*
=====================
AWS::RandomString
=====================
*/
std::string AWS::RandomString( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = ( sizeof( charset ) - 1 );
        return charset[rand() % max_index];
    };
    std::string str( length, 0 );
    std::generate_n( str.begin(), length, randchar );
    return str;
}
