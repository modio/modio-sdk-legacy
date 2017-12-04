#ifndef MODIO_RATINGS_H
#define MODIO_RATINGS_H

#include "Globals.h"
#include "data_containers/ModioRatings.h"

namespace modio
{
  class Ratings
  {
  public:
    u32 total_ratings;
    u32 positive_ratings;
    u32 negative_ratings;
    u32 percentage_positive;
    double weighted_aggregate;
    std::string display_text;

    void initialize(ModioRatings ratings);
  };
}

#endif
