
#include <iostream>
#include <string>

#include "./Server/Server.h"
#include "./Server/ServerHandler.h"

#include "./QTServerHandler.h"

const int PORT = 9999;

int main() {

  QTServerHandler* handler = new QTServerHandler();

  DeadSimpleRPC::Server server = DeadSimpleRPC::Server( ( DeadSimpleRPC::ServerHandler* ) handler );

  server.start( PORT );

  delete handler;

  return 0;
}
