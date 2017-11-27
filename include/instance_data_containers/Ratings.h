#ifndef MODIO_RATINGS_H
#define MODIO_RATINGS_H

#include "data_containers/ModioRatings.h"
#include "Globals.h"

namespace modio
{
  class Ratings
  {
  public:
    int total;
    int positive;
    int negative;
    int percentage;
    double weighted;
    std::string text;

    void initialize(ModioRatings ratings);
  };
}

#endif
