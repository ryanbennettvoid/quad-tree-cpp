#ifndef BOUNDARY_BOX_H
#define BOUNDARY_BOX_H

#include <string>

#include "./Printable.h"
#include "./Coordinate.h"

class BoundaryBox : Printable
{

  public:

    Coordinate mOrigin;
    double mHalfSize;

    BoundaryBox( Coordinate origin, double halfSize );
    bool containsCoordinate( Coordinate& origin ) const;
    bool intersectsBoundaryBox( BoundaryBox& boundaryBox ) const;

    // Printable
    std::string toString();

};

#endif
