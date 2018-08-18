#ifndef MODIO_ModioStats_H
#define MODIO_ModioStats_H

#include "../../dependencies/json/json.hpp"
#include "../../Utility.h"
#include "../ModioC.h"

using json = nlohmann::json;

extern "C"
{
  void modioInitStats(ModioStats* stats, json stats_json);
  void modioFreeStats(ModioStats* stats);
}

#endif