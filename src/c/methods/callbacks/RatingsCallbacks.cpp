#include "c/methods/callbacks/RatingsCallbacks.h"

std::map< u32, AddModRatingParams* > add_mod_rating_callbacks;

void modioOnAddModRating(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  add_mod_rating_callbacks[call_number]->callback(add_mod_rating_callbacks[call_number]->object, response);

  delete add_mod_rating_callbacks[call_number];
  add_mod_rating_callbacks.erase(call_number);
}
