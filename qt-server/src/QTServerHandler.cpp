
#include <iostream>
#include <string>

#include "../external/picojson.h"

#include "./QuadTree/Coordinate.h"
#include "./QuadTree/BoundaryBox.h"
#include "./QuadTree/Node.h"
#include "./QuadTree/Data.h"
#include "./QuadTree/QuadTree.h"
#include "./QuadTree/Renderer.h"

#include "./QTServerHandler.h"

const double HALF_WORLD_SIZE = 180;

QTServerHandler::QTServerHandler()
{
  BoundaryBox bb = BoundaryBox( Coordinate( 0, 0 ), HALF_WORLD_SIZE );
  this->mQuadTree = new QuadTree( bb );
}

std::string QTServerHandler::onRequest( std::string functionName, picojson::value args )
{

  picojson::object response = picojson::object();

  if ( functionName == "insert" ) {

    if ( !( args.get( "originX" ).is<double>() && args.get( "originY" ).is<double>() ) ) {
      std::cout << "invalid args for insert: " << args.serialize() << std::endl;
      return "{}";
    }

    double originX = args.get( "originX" ).get<double>();
    double originY = args.get( "originY" ).get<double>();
    Node node = Node( Coordinate( originX, originY ), Data() );
    response[ "success" ] = picojson::value( this->insert( node ) );

  } else if ( functionName == "queryRange" ) {

    if ( !( args.get( "origin" ).is<picojson::object>() && args.get( "halfSize" ).is<double>() ) ) {
      std::cout << "invalid args for queryRange: " << args.serialize() << std::endl;
      return "{}";
    }

    picojson::object origin = args.get( "origin" ).get<picojson::object>();

    if ( !( origin[ "x" ].is<double>() && origin[ "y" ].is<double>() ) ) {
      std::cout << "invalid args for queryRange: " << args.serialize() << std::endl;
      return "{}";
    }

    double originX = origin[ "x" ].get<double>();
    double originY = origin[ "y" ].get<double>();
    double halfSize = args.get( "halfSize" ).get<double>();

    BoundaryBox bb = BoundaryBox( Coordinate( originX, originY ), halfSize );

    std::vector<Node> nodeResults = this->queryRange( bb );

    std::cout << "queryRange results: " << nodeResults.size() << std::endl;

    picojson::array jsonResults = picojson::array();

    for ( unsigned int i = 0; i < nodeResults.size(); i++ ) {
      Node node = nodeResults[ i ];
      jsonResults.push_back( picojson::value( node.toJSON() ) );
    }

    response[ "items" ] = picojson::value( jsonResults );

  }

  picojson::value v = picojson::value( response );
  return v.serialize();

}

bool QTServerHandler::insert( Node node )
{
  if ( this->mQuadTree != NULL ) return this->mQuadTree->insert( node );
  return false;
}

std::vector<Node> QTServerHandler::queryRange( BoundaryBox bb )
{
  if ( this->mQuadTree != NULL ) return this->mQuadTree->queryRange( bb );
  return std::vector<Node>();
}