#include "c++/schemas/Stats.h"

namespace modio
{
void Stats::initialize(ModioStats modio_stats)
{
  this->mod_id = modio_stats.mod_id;
  this->popularity_rank_position = modio_stats.popularity_rank_position;
  this->popularity_rank_total_mods = modio_stats.popularity_rank_total_mods;
  this->downloads_total = modio_stats.downloads_total;
  this->subscribers_total = modio_stats.subscribers_total;
  this->ratings_total = modio_stats.ratings_total;
  this->ratings_positive = modio_stats.ratings_positive;
  this->ratings_negative = modio_stats.ratings_negative;
  this->ratings_percentage_positive = modio_stats.ratings_percentage_positive;
  this->ratings_weighted_aggregate = modio_stats.ratings_weighted_aggregate;
  if (modio_stats.ratings_display_text)
    this->ratings_display_text = modio_stats.ratings_display_text;
  this->date_expires = modio_stats.date_expires;
}

nlohmann::json toJson(Stats &stats)
{
  nlohmann::json stats_json;

  stats_json["mod_id"] = stats.mod_id;
  stats_json["popularity_rank_position"] = stats.popularity_rank_position;
  stats_json["popularity_rank_total_mods"] = stats.popularity_rank_total_mods;
  stats_json["downloads_total"] = stats.downloads_total;
  stats_json["subscribers_total"] = stats.subscribers_total;
  stats_json["ratings_total"] = stats.ratings_total;
  stats_json["ratings_positive"] = stats.ratings_positive;
  stats_json["ratings_negative"] = stats.ratings_negative;
  stats_json["ratings_percentage_positive"] = stats.ratings_percentage_positive;
  stats_json["ratings_weighted_aggregate"] = stats.ratings_weighted_aggregate;
  stats_json["ratings_display_text"] = stats.ratings_display_text;
  stats_json["date_expires"] = stats.date_expires;

  return stats_json;
}
} // namespace modio
