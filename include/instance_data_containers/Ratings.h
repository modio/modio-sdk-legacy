#ifndef MODIO_RATINGS_H
#define MODIO_RATINGS_H

#include "data_containers/ModioRatings.h"
#include "Globals.h"

namespace modio
{
  class Ratings
  {
  public:
    int total_ratings;
    int positive_ratings;
    int negative_ratings;
    int percentage_positive;
    double weighted_aggregate;
    std::string display_text;

    void initialize(ModioRatings ratings);
  };
}

#endif
