#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <random>

namespace Helpers
{

  // https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
  static int generateRandomNumberInRange( int a, int b )
  {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr( a, b ); // define the range
    return distr( eng );
  }
  
}

#endif
