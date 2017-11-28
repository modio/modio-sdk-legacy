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
    int total_ratings;
    int positive_ratings;
    int negative_ratings;
    double weighted_aggregate;
    int percentage_positive;
    char* display_text;
  };

  void modioInitRatings(ModioRatings* ratings, json ratings_json);
  void modioFreeRatings(ModioRatings* ratings);
}

#endif
