#include "c/schemas/ModioModStats.h"

extern "C"
{
  void modioInitModStats(ModioModStats* mod_stats, json mod_stats_json)
  {
    mod_stats->mod_id = 0;
    if(modio::hasKey(mod_stats_json, "mod_id"))
      mod_stats->mod_id = mod_stats_json["mod_id"];

    mod_stats->popularity_rank_position = 0;
    if(modio::hasKey(mod_stats_json, "popularity_rank_position"))
      mod_stats->popularity_rank_position = mod_stats_json["popularity_rank_position"];

    mod_stats->popularity_rank_total_mods = 0;
    if(modio::hasKey(mod_stats_json, "popularity_rank_total_mods"))
      mod_stats->popularity_rank_total_mods = mod_stats_json["popularity_rank_total_mods"];

    mod_stats->downloads_total = 0;
    if(modio::hasKey(mod_stats_json, "downloads_total"))
      mod_stats->downloads_total = mod_stats_json["downloads_total"];

    mod_stats->subscribers_total = 0;
    if(modio::hasKey(mod_stats_json, "subscribers_total"))
      mod_stats->subscribers_total = mod_stats_json["subscribers_total"];

    mod_stats->ratings_total = 0;
    if(modio::hasKey(mod_stats_json, "ratings_total"))
      mod_stats->ratings_total = mod_stats_json["ratings_total"];

    mod_stats->ratings_positive = 0;
    if(modio::hasKey(mod_stats_json, "ratings_positive"))
      mod_stats->ratings_positive = mod_stats_json["ratings_positive"];

    mod_stats->ratings_negative = 0;
    if(modio::hasKey(mod_stats_json, "ratings_negative"))
      mod_stats->ratings_negative = mod_stats_json["ratings_negative"];

    mod_stats->ratings_percentage_positive = 0;
    if(modio::hasKey(mod_stats_json, "ratings_percentage_positive"))
      mod_stats->ratings_percentage_positive = mod_stats_json["ratings_percentage_positive"];

    mod_stats->ratings_weighted_aggregate = 0;
    if(modio::hasKey(mod_stats_json, "ratings_weighted_aggregate"))
      mod_stats->ratings_weighted_aggregate = mod_stats_json["ratings_weighted_aggregate"];

    mod_stats->ratings_display_text = NULL;
    if(modio::hasKey(mod_stats_json, "ratings_display_text"))
    {
      std::string ratings_display_text_str = mod_stats_json["ratings_display_text"];
      mod_stats->ratings_display_text = new char[ratings_display_text_str.size() + 1];
      strcpy(mod_stats->ratings_display_text, ratings_display_text_str.c_str());
    }

    mod_stats->date_expires = 0;
    if(modio::hasKey(mod_stats_json, "date_expires"))
      mod_stats->date_expires = mod_stats_json["date_expires"];
  }

  void modioFreeModStats(ModioModStats* mod_stats)
  {
    if(mod_stats)
    {
      if(mod_stats->ratings_display_text)
        delete mod_stats->ratings_display_text;
    }
  }
}
