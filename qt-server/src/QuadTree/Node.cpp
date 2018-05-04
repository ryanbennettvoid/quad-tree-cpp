
#include <string>

#include "../../external/picojson.h"

#include "./Coordinate.h"
#include "./Data.h"

#include "./Node.h"

Node::Node( Coordinate origin, Data data )
: mOrigin(origin), mData(data)
{
}

picojson::object Node::toJSON()
{
  picojson::object o = picojson::object();
  o[ "x" ] = picojson::value( this->mOrigin.mX );
  o[ "y" ] = picojson::value( this->mOrigin.mY );
  o[ "data" ] = picojson::value( this->mData.mObject );
  return o;
}

// Printable
std::string Node::toString()
{
  return std::string( "Node(mOrigin:" + this->mOrigin.toString() + ",mData:" + this->mData.toString() + ")" );
}