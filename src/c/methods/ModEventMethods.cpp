#include "c/methods/ModEventMethods.h"

extern "C"
{
  struct GetAllModEventsParams
  {
    void* object;
    void (*callback)(void* object, ModioResponse response, ModioModEvent* mod_events_array, u32 mod_events_array_size);
  };

  std::map< u32, GetAllModEventsParams* > get_all_mod_events_callbacks;

  void modioOnGetAllModEvents(u32 call_number, u32 response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    ModioModEvent* mod_events_array = NULL;
    u32 mod_events_array_size = 0;
    if(response.code == 200)
    {
      try
      {
        if(modio::hasKey(response_json, "data"))
        {
          mod_events_array_size = response_json["data"].size();
          mod_events_array = new ModioModEvent[mod_events_array_size];

          for(u32 i=0; i<mod_events_array_size; i++)
          {
            modioInitModEvent(&(mod_events_array[i]), response_json["data"][i]);
          }
        }
      }catch(json::parse_error &e)
      {
        modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
      }
    }
    get_all_mod_events_callbacks[call_number]->callback(get_all_mod_events_callbacks[call_number]->object, response, mod_events_array, mod_events_array_size);

    for(u32 i=0; i<mod_events_array_size; i++)
    {
      modioFreeModEvent(&(mod_events_array[i]));
    }

    if(mod_events_array)
      delete[] mod_events_array;
    delete get_all_mod_events_callbacks[call_number];
    get_all_mod_events_callbacks.erase(call_number);
  }

  void modioGetAllModEvents(void* object, void (*callback)(void* object, ModioResponse response, ModioModEvent* mod_events_array, u32 mod_events_array_size))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/events";
    if(modio::API_KEY != "")
     url += "?api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_all_mod_events_callbacks[call_number] = new GetAllModEventsParams;
    get_all_mod_events_callbacks[call_number]->callback = callback;
    get_all_mod_events_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, headers, &modioOnGetAllModEvents);
  }
}
