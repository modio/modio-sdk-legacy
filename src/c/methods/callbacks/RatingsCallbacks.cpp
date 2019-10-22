#include "c/methods/callbacks/RatingsCallbacks.h"

std::map<u32, AddModRatingRequestParams *> add_mod_rating_callbacks;

void modioOnAddModRating(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  if(response_code >= 200 && response_code <300)
  {
    if(add_mod_rating_callbacks[call_number]->vote_up)
      modio::current_user_ratings[add_mod_rating_callbacks[call_number]->mod_id] = MODIO_RATING_POSITIVE;
    else
      modio::current_user_ratings[add_mod_rating_callbacks[call_number]->mod_id] = MODIO_RATING_NEGATIVE;
  }else
  {
    modio::current_user_ratings[add_mod_rating_callbacks[call_number]->mod_id] = MODIO_RATING_UNDEFINED;
  }
  

  add_mod_rating_callbacks[call_number]->callback(add_mod_rating_callbacks[call_number]->object, response);

  delete add_mod_rating_callbacks[call_number];
  add_mod_rating_callbacks.erase(call_number);
  
  modioFreeResponse(&response);
}

void clearRatingsCallbackParams()
{
  for (auto add_mod_rating_callback : add_mod_rating_callbacks)
    delete add_mod_rating_callback.second;
  add_mod_rating_callbacks.clear();
}
