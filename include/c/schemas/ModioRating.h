#ifndef MODIO_MODIORATING_H
#define MODIO_MODIORATING_H

#include "../../dependencies/json/json.hpp"
#include "../../Utility.h"
#include "../ModioC.h"

extern "C"
{
  void modioInitRating(ModioRating* rating, nlohmann::json rating_json);
  void modioFreeRating(ModioRating* rating);
}

#endif