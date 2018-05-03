#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <string>

#include "../../external/picojson.h"

namespace DeadSimpleRPC
{

  class ServerHandler
  {

    public:

      virtual std::string onRequest( std::string functionName, picojson::value args ) = 0;
    
  };

}

#endif
