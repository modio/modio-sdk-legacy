#include "c++/schemas/ModStats.h"

namespace modio
{
  void ModStats::initialize(ModioModStats modio_mod_stats)
  {
    this->mod_id = modio_mod_stats.mod_id;
    this->popularity_rank_position = modio_mod_stats.popularity_rank_position;
    this->popularity_rank_total_mods = modio_mod_stats.popularity_rank_total_mods;
    this->downloads_total = modio_mod_stats.downloads_total;
    this->subscribers_total = modio_mod_stats.subscribers_total;
    this->ratings_total = modio_mod_stats.ratings_total;
    this->ratings_positive = modio_mod_stats.ratings_positive;
    this->ratings_negative = modio_mod_stats.ratings_negative;
    this->ratings_percentage_positive = modio_mod_stats.ratings_percentage_positive;
    this->ratings_weighted_aggregate = modio_mod_stats.ratings_weighted_aggregate;
    if(modio_mod_stats.ratings_display_text)
      this->ratings_display_text = modio_mod_stats.ratings_display_text;
    this->date_expires = modio_mod_stats.date_expires;
  }

  json ModStats::toJson()
  {
    json mod_stats_json;
    mod_stats_json["mod_id"] = this->mod_id;
    mod_stats_json["popularity_rank_position"] = this->popularity_rank_position;
    mod_stats_json["popularity_rank_total_mods"] = this->popularity_rank_total_mods;
    mod_stats_json["downloads_total"] = this->downloads_total;
    mod_stats_json["subscribers_total"] = this->subscribers_total;
    mod_stats_json["ratings_total"] = this->ratings_total;
    mod_stats_json["ratings_positive"] = this->ratings_positive;
    mod_stats_json["ratings_negative"] = this->ratings_negative;
    mod_stats_json["ratings_percentage_positive"] = this->ratings_percentage_positive;
    mod_stats_json["ratings_weighted_aggregate"] = this->ratings_weighted_aggregate;
    mod_stats_json["ratings_display_text"] = this->ratings_display_text;
    mod_stats_json["date_expires"] = this->date_expires;
    return mod_stats_json;
  }
}
