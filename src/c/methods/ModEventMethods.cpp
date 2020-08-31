#include <map>                                         // for map
#include <string>                                      // for allocator, ope...
#include "wrappers/CurlWrapper.h"      // for get, getCallNu...
#include "Utility.h"       // for toString, getH...
#include "c/ModioC.h"           // for u32, ModioModE...
#include "c/creators/ModioFilterCreator.h"  // for getFilterString
#include "Globals.h"      // for API_KEY, GAME_ID
#include "c/methods/callbacks/ModEventCallbacks.h"     // for GetAllEventsPa...
#include "dependencies/nlohmann/json.hpp"              // for json

extern "C"
{
  void modioGetEventsFilterString(void* object, u32 mod_id, char const* filter_string, u32 cache_max_age_seconds, void (*callback)(void* object, ModioResponse response, ModioModEvent* events_array, u32 events_array_size))
  {
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/events?" + (filter_string ? filter_string : "") + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_events_callbacks[call_number] = new GetEventsParams;
    get_events_callbacks[call_number]->callback = callback;
    get_events_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetEvents);
  }

  void modioGetEvents(void* object, u32 mod_id, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioModEvent* events_array, u32 events_array_size))
  {
    std::string filter_string = modio::getFilterString(&filter);
    modioGetEventsFilterString(object, mod_id, filter_string.c_str(), filter.cache_max_age_seconds, callback);
  }

  void modioGetAllEventsFilterString(void* object, char const* filter_string, u32 cache_max_age_seconds, void (*callback)(void* object, ModioResponse response, ModioModEvent* events_array, u32 events_array_size))
  {
    cache_max_age_seconds = 60;
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/events?" + (filter_string ? filter_string : "") + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_all_events_callbacks[call_number] = new GetAllEventsParams;
    get_all_events_callbacks[call_number]->callback = callback;
    get_all_events_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetAllEvents);
  }

  void modioGetAllEvents(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioModEvent* events_array, u32 events_array_size))
  {
    std::string filter_string = modio::getFilterString(&filter);
    modioGetAllEventsFilterString(object, filter_string.c_str(), filter.cache_max_age_seconds, callback);
  }

  void modioSetEventListener(void (*callback)(ModioResponse response, ModioModEvent* events_array, u32 events_array_size))
  {
    modio::event_listener_callback = callback;
  }
}
