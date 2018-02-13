#include "c/schemas/ModioRatingSummary.h"

extern "C"
{
  void modioInitRatingSummary(ModioRatingSummary* ratings, json ratings_json)
  {
    ratings->total_ratings = 0;
    if(modio::hasKey(ratings_json, "total_ratings"))
      ratings->total_ratings = ratings_json["total_ratings"];

    ratings->positive_ratings = 0;
    if(modio::hasKey(ratings_json, "positive_ratings"))
      ratings->positive_ratings = ratings_json["positive_ratings"];

    ratings->negative_ratings = 0;
    if(modio::hasKey(ratings_json, "negative_ratings"))
      ratings->negative_ratings = ratings_json["negative_ratings"];

    ratings->percentage_positive = 0;
    if(modio::hasKey(ratings_json, "percentage_positive"))
      ratings->percentage_positive = ratings_json["percentage_positive"];

    ratings->weighted_aggregate = -1;
    if(modio::hasKey(ratings_json, "weighted_aggregate"))
      ratings->weighted_aggregate = ratings_json["weighted_aggregate"];

    ratings->display_text = NULL;
    if(modio::hasKey(ratings_json, "display_text"))
    {
      std::string display_text_str = ratings_json["display_text"];
      ratings->display_text = new char[display_text_str.size() + 1];
      strcpy(ratings->display_text, display_text_str.c_str());
    }
  }

  void modioFreeRatingSummary(ModioRatingSummary* ratings)
  {
    if(ratings)
    {
      if(ratings->display_text)
        delete[] ratings->display_text;
    }
  }
}
