#include "c/methods/callbacks/ModStatsCallbacks.h"

std::map< u32,GetModStatsParams* > get_mod_stats_callbacks;

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