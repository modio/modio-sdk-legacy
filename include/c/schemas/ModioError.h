#ifndef MODIO_MODIOERROR_H
#define MODIO_MODIOERROR_H

#include "../../dependencies/json/json.hpp"
#include "../../Utility.h"
#include "../ModioC.h"

extern "C"
{
  void modioInitError(ModioError* error, nlohmann::json image_json);
  void modioFreeError(ModioError* error);
}

#endif
