namespace modio
{
  struct GetModStatsCall
  {
    const std::function<void(const modio::Response&, const modio::ModStats& mod_stats)> callback;
  };

  struct GetAllModStatsCall
  {
    const std::function<void(const modio::Response&, std::vector<modio::ModStats>& mods_stats)> callback;
  };

  extern std::map<u32, GetModStatsCall*> get_mod_stats_calls;
  extern std::map<u32, GetAllModStatsCall*> get_all_mod_stats_calls;

  void onGetModStats(void* object, ModioResponse modio_response, ModioModStats mod_stats);
  void onGetAllModStats(void* object, ModioResponse modio_response, ModioModStats mod_stats[], u32 mod_stats_size);
}
