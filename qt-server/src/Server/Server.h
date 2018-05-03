#ifndef SERVER_H
#define SERVER_H

#include "./ServerHandler.h"

namespace DeadSimpleRPC
{

  class Server
  {

    private:

      bool mDoExit;
      int mPort;
      ServerHandler* mHandler;

    public:

      Server( ServerHandler* handler );
      ~Server();

      void start( int port );
      void stop();
      void handleRequest( std::string request );


  };
  
}

#endif
