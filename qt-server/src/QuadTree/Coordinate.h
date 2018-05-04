#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>

#include "../Misc/Printable.h"

class Coordinate : Printable
{

  public:

    double mX;
    double mY;

    Coordinate( double x, double y );

    // Printable
    std::string toString();


};

#endif
