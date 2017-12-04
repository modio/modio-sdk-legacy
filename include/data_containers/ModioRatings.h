#ifndef MODIO_MODIORATINGS_H
#define MODIO_MODIORATINGS_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
;
using json = nlohmann::json;

extern "C"
{
  struct ModioRatings
  {
    u32 total_ratings;
    u32 positive_ratings;
    u32 negative_ratings;
    u32 percentage_positive;
    double weighted_aggregate;
    char* display_text;
  };

  void modioInitRatings(ModioRatings* ratings, json ratings_json);
  void modioFreeRatings(ModioRatings* ratings);
}

#endif
