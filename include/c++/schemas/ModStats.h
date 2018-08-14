#ifndef MODIO_MODSTATS_H
#define MODIO_MODSTATS_H

#include "../../Utility.h"
#include "../../Globals.h"
#include "../../ModUtility.h"
#include "../../c/schemas/ModioModStats.h"

namespace modio
{
  class ModStats
  {
  public:
    u32 mod_id;
    u32 popularity_rank_position;
    u32 popularity_rank_total_mods;
    u32 downloads_total;
    u32 subscribers_total;
    u32 ratings_total;
    u32 ratings_positive;
    u32 ratings_negative;
    u32 ratings_percentage_positive;
    double ratings_weighted_aggregate;
    std::string ratings_display_text;
    u32 date_expires;

    void initialize(ModioModStats mod);
    json toJson();
  };
}

#endif
