#include "c/methods/ModEventMethods.h"

extern "C"
{
  void modioGetEvents(void* object, u32 mod_id, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioEvent* events_array, u32 events_array_size))
  {
    std::string filter_string = modio::getFilterString(&filter);

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/events?" + filter_string + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_events_callbacks[call_number] = new GetEventsParams;
    get_events_callbacks[call_number]->callback = callback;
    get_events_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetEvents);
  }

  void modioGetAllEvents(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioEvent* events_array, u32 events_array_size))
  {
    std::string filter_string = modio::getFilterString(&filter);

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/events?" + filter_string + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_all_events_callbacks[call_number] = new GetAllEventsParams;
    get_all_events_callbacks[call_number]->callback = callback;
    get_all_events_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetAllEvents);
  }

  void modioSetEventListener(void (*callback)(ModioResponse response, ModioEvent* events_array, u32 events_array_size))
  {
    modio::event_listener_callback = callback;
  }
}
