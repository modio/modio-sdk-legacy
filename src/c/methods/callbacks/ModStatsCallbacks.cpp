#include "c/methods/callbacks/ModStatsCallbacks.h"

std::map< u32,GetModStatsParams* > get_mod_stats_callbacks;
std::map< u32,GetAllModStatsParams* > get_all_mod_stats_callbacks;

void modioOnGetModStats(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioModStats mod_stats;
  modioInitModStats(&mod_stats, response_json);

  get_mod_stats_callbacks[call_number]->callback(get_mod_stats_callbacks[call_number]->object, response, mod_stats);

  delete get_mod_stats_callbacks[call_number];

  get_mod_stats_callbacks.erase(call_number);

  modioFreeResponse(&response);
  modioFreeModStats(&mod_stats);
}

void modioOnGetAllModStats(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  if(response.code == 200)
  {
    if(!get_all_mod_stats_callbacks[call_number]->is_cache)
      modio::addCallToCache(get_all_mod_stats_callbacks[call_number]->url, response_json);

    u32 mods_stats_size = (u32)response_json["data"].size();
    ModioModStats* mods_stats = new ModioModStats[mods_stats_size];
    for(u32 i=0; i<mods_stats_size; i++)
    {
      modioInitModStats(&mods_stats[i], response_json["data"][i]);
    }

    get_all_mod_stats_callbacks[call_number]->callback(get_all_mod_stats_callbacks[call_number]->object, response, mods_stats, mods_stats_size);
    
    for(u32 i=0; i<mods_stats_size; i++)
    {
      modioFreeModStats(&mods_stats[i]);
    }

    delete[] mods_stats;
  }else
  {
    get_all_mod_stats_callbacks[call_number]->callback(get_all_mod_stats_callbacks[call_number]->object, response, NULL, 0);
  }
  delete get_all_mod_stats_callbacks[call_number];
  get_all_mod_stats_callbacks.erase(call_number);
  modioFreeResponse(&response);
}