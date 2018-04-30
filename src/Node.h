#ifndef NODE_H
#define NODE_H

#include <string>

#include "./Printable.h"
#include "./Coordinate.h"
#include "./Data.h"

class Node : Printable
{

  public:

    Coordinate mOrigin;
    Data mData;

    Node( Coordinate origin, Data data );

    // Printable
    std::string toString();

};

#endif
