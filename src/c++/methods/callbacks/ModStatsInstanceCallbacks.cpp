#include "c++/ModIOInstance.h"

namespace modio
{
  std::map<u32, GetModStatsCall*> get_mod_stats_calls;
  std::map<u32, GetAllModStatsCall*> get_all_mod_stats_calls;

  void onGetModStats(void* object, ModioResponse modio_response, ModioModStats modio_mod_stats)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    modio::ModStats mod_stats;

    if(modio_response.code == 200)
    {
      mod_stats.initialize(modio_mod_stats);
    }

    get_mod_stats_calls[call_id]->callback((const Response&)response, mod_stats);

    delete (u32*)object;
    delete get_mod_stats_calls[call_id];
    get_mod_stats_calls.erase(call_id);
  }

  void onGetAllModStats(void* object, ModioResponse modio_response, ModioModStats modio_mod_stats[], u32 modio_mod_stats_size)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    std::vector<modio::ModStats> mod_stats_vector;
    mod_stats_vector.resize(modio_mod_stats_size);
    for(u32 i=0; i < modio_mod_stats_size; i++)
    {
      mod_stats_vector[i].initialize(modio_mod_stats[i]);
    }

    get_all_mod_stats_calls[call_id]->callback((const Response&)response, mod_stats_vector);

    delete (u32*)object;
    delete get_all_mod_stats_calls[call_id];
    get_all_mod_stats_calls.erase(call_id);
  }
}