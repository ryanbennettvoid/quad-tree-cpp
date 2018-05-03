#ifndef QT_SERVER_HANDLER_H
#define QT_SERVER_HANDLER_H

#include <string>
#include <vector>

#include "../external/picojson.h"

#include "./QuadTree/Coordinate.h"
#include "./QuadTree/BoundaryBox.h"
#include "./QuadTree/Node.h"
#include "./QuadTree/Data.h"
#include "./QuadTree/QuadTree.h"
#include "./QuadTree/Renderer.h"

#include "./Server/ServerHandler.h"

class QTServerHandler : DeadSimpleRPC::ServerHandler
{

  private:

    QuadTree* mQuadTree;
  
  public:

    QTServerHandler();
  
    std::string onRequest( std::string functionName, picojson::value args );
    bool insert( Node node );
    std::vector<Node> queryRange( BoundaryBox bb );

};

#endif
