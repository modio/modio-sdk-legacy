#ifndef MODIO_ModioStats_H
#define MODIO_ModioStats_H

#include "../../dependencies/json/json.hpp"
#include "../../Utility.h"
#include "../ModioC.h"

extern "C"
{
  void modioInitStats(ModioStats* stats, nlohmann::json stats_json);
  void modioFreeStats(ModioStats* stats);
}

#endif