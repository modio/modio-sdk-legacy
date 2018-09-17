#include "c/schemas/ModioRating.h"

extern "C"
{
  void modioInitRating(ModioRating* rating, nlohmann::json rating_json)
  {
    rating->game_id = 0;
    if(modio::hasKey(rating_json, "game_id"))
      rating->game_id = rating_json["game_id"];
    
    rating->mod_id = 0;
    if(modio::hasKey(rating_json, "mod_id"))
      rating->mod_id = rating_json["mod_id"];
    
    rating->rating = 0;
    if(modio::hasKey(rating_json, "rating"))
      rating->rating = rating_json["rating"];
    
    rating->date_added = 0;
    if(modio::hasKey(rating_json, "date_added"))
      rating->date_added = rating_json["date_added"];
  }

  void modioFreeRating(ModioRating* rating)
  {
  }
}
