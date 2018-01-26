#include "c/methods/ModEventMethods.h"

extern "C"
{
  void modioGetAllModEvents(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioModEvent* mod_events_array, u32 mod_events_array_size))
  {
    std::string filter_string = modio::getFilterString(&filter);

    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/events?" + filter_string + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_all_mod_events_callbacks[call_number] = new GetAllModEventsParams;
    get_all_mod_events_callbacks[call_number]->callback = callback;
    get_all_mod_events_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, headers, &modioOnGetAllModEvents);
  }

  void modioListendToEvents(void (*callback)(ModioResponse response, ModioModEvent* mod_events_array, u32 mod_events_array_size))
  {
    modio::callback = callback;
  }
}
