#ifndef MODIO_RATINGS_H
#define MODIO_RATINGS_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct ModioRatings
  {
    int total;
    int positive;
    int negative;
    double weighted;
    int percentage;
    int stars;
    char* text;
  };

  void modioInitRatings(ModioRatings* ratings, json ratings_json);
  void modioFreeRatings(ModioRatings* ratings);
}

#endif
