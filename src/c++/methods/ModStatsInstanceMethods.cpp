#include "c++/ModIOInstance.h"

namespace modio
{
  void Instance::getModStats(u32 mod_id, const std::function<void(const modio::Response& response, const modio::Stats& stats)>& callback)
  {
    const struct GetModStatsCall* get_mod_stats_call = new GetModStatsCall{callback};
    get_mod_stats_calls[this->current_call_id] = (GetModStatsCall*)get_mod_stats_call;

    modioGetModStats((void*)new u32(this->current_call_id), mod_id, &onGetModStats);

    this->current_call_id++;
  }

  void Instance::getAllModStats(modio::FilterCreator& filter, const std::function<void(const modio::Response&, const std::vector<modio::Stats> & mods_stats)>& callback)
  {
    const struct GetAllModStatsCall* get_all_mod_stats_call = new GetAllModStatsCall{callback};
    get_all_mod_stats_calls[this->current_call_id] = (GetAllModStatsCall*)get_all_mod_stats_call;

    modioGetAllModStats((void*)new u32(this->current_call_id), *filter.getFilter(), &onGetAllModStats);

    this->current_call_id++;
  }
}