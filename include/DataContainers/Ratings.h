#ifndef MODWORKS_RATINGS
#define MODWORKS_RATINGS

#include "json/json.hpp"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

namespace modworks
{
  class Ratings
  {
  public:
    Ratings(json ratings_json);
    int total;
    int positive;
    int negative;
    double weighted;
    int percentage;
    int stars;
    string text;
  };
}

#endif
