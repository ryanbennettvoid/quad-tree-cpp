
#include <string>

#include "./Coordinate.h"

Coordinate::Coordinate( double x, double y )
: mX(x), mY(y)
{
}

// Printable
std::string Coordinate::toString()
{
  return std::string( "Coordinate(mX:" + std::to_string( this->mX ) + ",mY:" + std::to_string( this->mY ) + ")" );
}
