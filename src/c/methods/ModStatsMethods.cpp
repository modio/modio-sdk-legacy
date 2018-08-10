#include "c/methods/ModStatsMethods.h"

extern "C"
{
  void modioGetModStats(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioModStats mod))
  {
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/stats?api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_mod_stats_callbacks[call_number] = new GetModStatsParams;
    get_mod_stats_callbacks[call_number]->callback = callback;
    get_mod_stats_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetModStats);
  }
}
