#include "c/methods/RatingsMethods.h"

extern "C"
{
  void modioAddModRating(void* object, u32 mod_id, bool vote_up, void (*callback)(void *object, ModioResponse response))
  {
    std::map<std::string, std::string> data;

    u32 call_number = modio::curlwrapper::getCallNumber();

    add_mod_rating_callbacks[call_number] = new GenericRequestParams;
    add_mod_rating_callbacks[call_number]->callback = callback;
    add_mod_rating_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/ratings";

    if(vote_up)
    {
      url += "?rating=1";
    }else
    {
      url += "?rating=-1";
    }

    modio::curlwrapper::post(call_number, url, modio::getUrlEncodedHeaders(), data, &modioOnAddModRating);
  }
}
