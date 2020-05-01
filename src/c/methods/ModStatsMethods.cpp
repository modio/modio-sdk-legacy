#include <map>                                                  // for map
#include <string>                                               // for alloc...
#include "ModUtility.h"                                         // for getCa...
#include "dependencies/nlohmann/json.hpp"     // for json
#include "c/ModioC.h"                                // for u32
#include "c/creators/ModioFilterCreator.h"           // for getFi...
#include "Globals.h"               // for API_KEY
#include "Utility.h"   // for toString
#include "wrappers/CurlWrapper.h"  // for get
#include "c/methods/callbacks/ModStatsCallbacks.h"              // for GetAl...

extern "C"
{
  void modioGetModStats(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioStats mod))
  {
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/stats?api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_mod_stats_callbacks[call_number] = new GetModStatsParams;
    get_mod_stats_callbacks[call_number]->callback = callback;
    get_mod_stats_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetModStats);
  }

  void modioGetAllModStatsFilterString(void* object, char const* filter_string, u32 cache_max_age_seconds, void (*callback)(void* object, ModioResponse response, ModioStats mods_stats[], u32 mods_stats_size))
  {
    std::string url_without_api_key = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/stats?" + (filter_string ? filter_string : "");
    std::string url = url_without_api_key + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_all_mod_stats_callbacks[call_number] = new GetAllModStatsParams;
    get_all_mod_stats_callbacks[call_number]->callback = callback;
    get_all_mod_stats_callbacks[call_number]->object = object;
    get_all_mod_stats_callbacks[call_number]->url = url_without_api_key;
    get_all_mod_stats_callbacks[call_number]->is_cache = false;

    std::string cache_filename = modio::getCallFileFromCache(url_without_api_key, cache_max_age_seconds);
    if(cache_filename != "")
    {
      nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache/" + cache_filename);
      nlohmann::json empty_json = {};
      if(!cache_file_json.empty())
      {
        get_all_mod_stats_callbacks[call_number]->is_cache = true;
        modioOnGetAllModStats(call_number, 200, cache_file_json);
        return;
      }
    }
    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetAllModStats);
  }

  void modioGetAllModStats(void* object, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioStats mods_stats[], u32 mods_stats_size))
  {
    std::string filter_string = modio::getFilterString(&filter);
    modioGetAllModStatsFilterString(object, filter_string.c_str(), filter.cache_max_age_seconds, callback);
  }
}
