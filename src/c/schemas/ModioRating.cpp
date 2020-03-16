#include "c/schemas/ModioRating.h"
#include "Utility.h"                // for hasKey
#include "c/ModioC.h"               // for ModioDownload

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

  void modioInitRatingCpp(ModioRating* modio_rating, modio::Rating* rating)
  {
    modio_rating->game_id = rating->game_id;
    modio_rating->mod_id = rating->mod_id;
    modio_rating->rating = rating->rating;
    modio_rating->date_added = rating->date_added;
  }

  void modioFreeRating(ModioRating* rating)
  {
  }
}
