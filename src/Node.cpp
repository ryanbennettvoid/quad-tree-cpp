
#include <string>

#include "./Node.h"
#include "./Coordinate.h"
#include "./Data.h"

Node::Node( Coordinate origin, Data data )
: mOrigin(origin), mData(data)
{
}

// Printable
std::string Node::toString()
{
  return std::string( "Node(mOrigin:" + this->mOrigin.toString() + ",mData:" + this->mData.toString() + ")" );
}
