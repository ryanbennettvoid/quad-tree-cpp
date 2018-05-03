#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "../../external/picojson.h"

#include "./ServerHandler.h"

#include "./Server.h"


DeadSimpleRPC::Server::Server( ServerHandler* handler )
: mDoExit(false), mHandler(handler)
{
}

DeadSimpleRPC::Server::~Server()
{
}

void DeadSimpleRPC::Server::start( int port )
{

  this->mDoExit = false;
  this->mPort = port;

  int sock;
  struct sockaddr_in server;
  char buff[ 1024 ];
  int rval;

  sock = socket( AF_INET, SOCK_STREAM, 0 );

  if ( sock < 0 ) {
    throw std::string( "failed to create socket: " + std::to_string( sock ) + "\n" );
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons( this->mPort );

  if ( bind( sock, ( struct sockaddr * ) &server, sizeof( server ) ) ) {
    throw std::string( "bind failed\n" );
  }

  std::cout << "listening on port " << this->mPort << std::endl;

  listen( sock, 100 ); // num connections

  int newsock;

  do {

    newsock = accept( sock, ( struct sockaddr * ) 0, 0 );

    if ( newsock == -1 ) {
      throw std::string( "accept failed\n" );
    } else {

      memset( buff, 0, sizeof( buff ) );

      rval = recv( newsock, buff, sizeof( buff ), 0 );

      if ( rval < 0 ) {
        throw std::string( "reading error message\n" );
      } else if ( rval == 0 ) {
        std::cout << "ending connection\n" << std::endl;
      } else {
        
        picojson::value v;
        std::string err = picojson::parse( v, std::string( buff ) );

        if ( !err.empty() ) {
          std::cerr << err << std::endl;
        }

        const std::string& functionName = v.get( "functionName" ).to_str();
        const picojson::value& args = v.get( "args" );

        if ( this->mHandler != NULL ) {
          std::string response = this->mHandler->onRequest( functionName, args );
          const char *str = response.c_str();
          send( newsock, str, strlen( str ), 0 );
        }
        
      }

    }

    close( newsock );

  } while ( !this->mDoExit );

}

void DeadSimpleRPC::Server::stop()
{
  this->mDoExit = true;
}
