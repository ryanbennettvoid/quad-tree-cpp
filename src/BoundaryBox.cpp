
#include <string>

#include "./Coordinate.h"
#include "./BoundaryBox.h"

BoundaryBox::BoundaryBox( Coordinate origin, double halfSize )
: mOrigin(origin), mHalfSize(halfSize)
{
}

bool BoundaryBox::containsCoordinate( Coordinate& coordinate ) const
{

  double left     = this->mOrigin.mX - this->mHalfSize;
  double right    = this->mOrigin.mX + this->mHalfSize;
  double top      = this->mOrigin.mY + this->mHalfSize;
  double bottom   = this->mOrigin.mY - this->mHalfSize;

  double x = coordinate.mX;
  double y = coordinate.mY;

  if ( left < x && x < right && bottom < y && y < top ) {
    return true;
  }

  return false;
}

// https://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
bool BoundaryBox::intersectsBoundaryBox( BoundaryBox& boundaryBox ) const
{

  double leftA    = this->getLeft();
  double rightA   = this->getRight();
  double topA     = this->getTop();
  double bottomA  = this->getBottom();

  double leftB    = boundaryBox.getLeft();
  double rightB   = boundaryBox.getRight();
  double topB     = boundaryBox.getTop();
  double bottomB  = boundaryBox.getBottom();

  return !( leftA > rightB || rightA < leftB || topA < bottomB || bottomA > topB );
}

double BoundaryBox::getLeft() const
{
  return this->mOrigin.mX - this->mHalfSize;
}

double BoundaryBox::getRight() const
{
  return this->mOrigin.mX + this->mHalfSize;
}

double BoundaryBox::getTop() const
{
  return this->mOrigin.mY + this->mHalfSize;
}

double BoundaryBox::getBottom() const
{
  return this->mOrigin.mY - this->mHalfSize;
}



// Printable
std::string BoundaryBox::toString()
{
  return std::string( "BoundaryBox(mOrigin:" + this->mOrigin.toString() + ",mHalfSize:" + std::to_string( this->mHalfSize ) + ")" );
}
