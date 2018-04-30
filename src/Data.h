#ifndef DATA_H
#define DATA_H

#include <string>

#include "./Printable.h"

class Data : Printable
{
  
  public:

    Data();

    // Printable
    std::string toString();

};

#endif
