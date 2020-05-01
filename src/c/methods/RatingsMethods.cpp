#include <map>                                                  // for map
#include <string>                                               // for string
#include "dependencies/nlohmann/json.hpp"     // for json
#include "c/ModioC.h"                                // for u32
#include "Globals.h"               // for curre...
#include "Utility.h"   // for toString
#include "wrappers/CurlWrapper.h"  // for getCa...
#include "c/methods/callbacks/RatingsCallbacks.h"               // for AddMo...

extern "C"
{
  void modioAddModRating(void* object, u32 mod_id, bool vote_up, void (*callback)(void *object, ModioResponse response))
  {
    if(!modioIsLoggedIn())
    {
      modio::processGenericLocalUnauthorizedRequest(object, callback);
      return;
    }
    
    std::map<std::string, std::string> data;

    u32 call_number = modio::curlwrapper::getCallNumber();

    add_mod_rating_callbacks[call_number] = new AddModRatingRequestParams;
    add_mod_rating_callbacks[call_number]->callback = callback;
    add_mod_rating_callbacks[call_number]->object = object;
    add_mod_rating_callbacks[call_number]->mod_id = mod_id;
    add_mod_rating_callbacks[call_number]->vote_up = vote_up;

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

  u32 modioGetCurrentUserModRating(u32 mod_id)
  {
    if ( modio::current_user_ratings.find(mod_id) == modio::current_user_ratings.end() )
      return MODIO_RATING_UNDEFINED;
    return modio::current_user_ratings[mod_id];
  }
}
