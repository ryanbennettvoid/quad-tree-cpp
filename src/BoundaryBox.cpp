
#include <string>

#include "./Coordinate.h"
#include "./BoundaryBox.h"

BoundaryBox::BoundaryBox( Coordinate origin, double halfSize )
: mOrigin(origin), mHalfSize(halfSize)
{
}

bool BoundaryBox::containsCoordinate( Coordinate& coordinate ) const
{

  double left = this->mOrigin.mX - this->mHalfSize;
  double right = this->mOrigin.mX + this->mHalfSize;
  double top = this->mOrigin.mY + this->mHalfSize;
  double bottom = this->mOrigin.mY - this->mHalfSize;

  double x = coordinate.mX;
  double y = coordinate.mY;

  if (
    left < x && x < right &&
    bottom < y && y < top
  ) {
    return true;
  }

  return false;
}

// https://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
bool BoundaryBox::intersectsBoundaryBox( BoundaryBox& boundaryBox ) const
{

  double leftA = this->mOrigin.mX - this->mHalfSize;
  double rightA = this->mOrigin.mX + this->mHalfSize;
  double topA = this->mOrigin.mY + this->mHalfSize;
  double bottomA = this->mOrigin.mY - this->mHalfSize;

  double leftB = boundaryBox.mOrigin.mX - boundaryBox.mHalfSize;
  double rightB = boundaryBox.mOrigin.mX + boundaryBox.mHalfSize;
  double topB = boundaryBox.mOrigin.mY + boundaryBox.mHalfSize;
  double bottomB = boundaryBox.mOrigin.mY - boundaryBox.mHalfSize;

  return !(
    leftA > rightB ||
    rightA < leftB ||
    topA < bottomB ||
    bottomA > topB
  );
}


// Printable
std::string BoundaryBox::toString()
{
  return std::string( "BoundaryBox(mOrigin:" + this->mOrigin.toString() + ",mHalfSize:" + std::to_string( this->mHalfSize ) + ")" );
}
