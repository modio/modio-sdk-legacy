#ifndef MODIO_MODIOMODSTATS_H
#define MODIO_MODIOMODSTATS_H

#include "../../dependencies/json/json.hpp"
#include "../../Utility.h"
#include "../ModioC.h"

using json = nlohmann::json;

extern "C"
{
  void modioInitModStats(ModioModStats* mod_stats, json mod_stats_json);
  void modioFreeModStats(ModioModStats* mod_stats);
}

#endif