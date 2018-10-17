#include "c/schemas/ModioStats.h"

extern "C"
{
  void modioInitStats(ModioStats* stats, nlohmann::json stats_json)
  {
    stats->mod_id = 0;
    if(modio::hasKey(stats_json, "mod_id"))
      stats->mod_id = stats_json["mod_id"];

    stats->popularity_rank_position = 0;
    if(modio::hasKey(stats_json, "popularity_rank_position"))
      stats->popularity_rank_position = stats_json["popularity_rank_position"];

    stats->popularity_rank_total_mods = 0;
    if(modio::hasKey(stats_json, "popularity_rank_total_mods"))
      stats->popularity_rank_total_mods = stats_json["popularity_rank_total_mods"];

    stats->downloads_total = 0;
    if(modio::hasKey(stats_json, "downloads_total"))
      stats->downloads_total = stats_json["downloads_total"];

    stats->subscribers_total = 0;
    if(modio::hasKey(stats_json, "subscribers_total"))
      stats->subscribers_total = stats_json["subscribers_total"];

    stats->ratings_total = 0;
    if(modio::hasKey(stats_json, "ratings_total"))
      stats->ratings_total = stats_json["ratings_total"];

    stats->ratings_positive = 0;
    if(modio::hasKey(stats_json, "ratings_positive"))
      stats->ratings_positive = stats_json["ratings_positive"];

    stats->ratings_negative = 0;
    if(modio::hasKey(stats_json, "ratings_negative"))
      stats->ratings_negative = stats_json["ratings_negative"];

    stats->ratings_percentage_positive = 0;
    if(modio::hasKey(stats_json, "ratings_percentage_positive"))
      stats->ratings_percentage_positive = stats_json["ratings_percentage_positive"];

    stats->ratings_weighted_aggregate = 0;
    if(modio::hasKey(stats_json, "ratings_weighted_aggregate"))
      stats->ratings_weighted_aggregate = stats_json["ratings_weighted_aggregate"];

    stats->ratings_display_text = NULL;
    if(modio::hasKey(stats_json, "ratings_display_text"))
    {
      std::string ratings_display_text_str = stats_json["ratings_display_text"];
      stats->ratings_display_text = new char[ratings_display_text_str.size() + 1];
      strcpy(stats->ratings_display_text, ratings_display_text_str.c_str());
    }

    stats->date_expires = 0;
    if(modio::hasKey(stats_json, "date_expires"))
      stats->date_expires = stats_json["date_expires"];
  }

  void modioFreeStats(ModioStats* stats)
  {
    if(stats)
    {
      if(stats->ratings_display_text)
        delete[] stats->ratings_display_text;
    }
  }
}
