#ifndef DATA_H
#define DATA_H

#include <string>

#include "../../external/picojson.h"

#include "../Misc/Printable.h"

class Data : Printable
{
  
  public:

    picojson::object mObject;

    Data( picojson::object data );

    // Printable
    std::string toString();

};

#endif
