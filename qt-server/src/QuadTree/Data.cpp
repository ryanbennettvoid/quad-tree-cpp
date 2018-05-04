
#include <string>

#include "../../external/picojson.h"

#include "./Data.h"

Data::Data( picojson::object data )
: mObject(data)
{
}

std::string Data::toString()
{
  return picojson::value( this->mObject ).serialize();
}
