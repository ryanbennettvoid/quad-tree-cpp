#ifndef NODE_H
#define NODE_H

#include <string>

#include "../../external/picojson.h"

#include "./Coordinate.h"
#include "./Data.h"

#include "../Misc/Printable.h"

class Node : Printable
{

  public:

    Coordinate mOrigin;
    Data mData;

    Node( Coordinate origin, Data data );
    picojson::object toJSON();

    // Printable
    std::string toString();

};

#endif
