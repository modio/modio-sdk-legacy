#ifndef MODIO_RATINGS_H
#define MODIO_RATINGS_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

namespace modio
{
  struct Ratings
  {
    int total;
    int positive;
    int negative;
    double weighted;
    int percentage;
    int stars;
    string text;
  };

  void initRatings(Ratings* ratings, json ratings_json);
  void freeRatings(Ratings* ratings);
}

#endif
