#include "data_containers/Ratings.h"

extern "C"
{
  void modioInitRatings(ModioRatings* ratings, json ratings_json)
  {
    ratings->total = -1;
    if(modio::hasKey(ratings_json, "total"))
      ratings->total = ratings_json["total"];

    ratings->positive = -1;
    if(modio::hasKey(ratings_json, "positive"))
      ratings->positive = ratings_json["positive"];

    ratings->negative = -1;
    if(modio::hasKey(ratings_json, "negative"))
      ratings->negative = ratings_json["negative"];

    ratings->weighted = -1;
    if(modio::hasKey(ratings_json, "weighted"))
      ratings->weighted = ratings_json["weighted"];

    ratings->percentage = -1;
    if(modio::hasKey(ratings_json, "percentage"))
      ratings->percentage = ratings_json["percentage"];

    ratings->stars = -1;
    if(modio::hasKey(ratings_json, "stars"))
      ratings->stars = ratings_json["stars"];

    ratings->text = "";
    if(modio::hasKey(ratings_json, "text"))
      ratings->text = ratings_json["text"];
  }

  void modioFreeRatings(ModioRatings* ratings)
  {
    delete ratings;
  }
}
