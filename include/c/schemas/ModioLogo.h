#ifndef MODIO_MODIOLOGO_H
#define MODIO_MODIOLOGO_H

#include "../../dependencies/json/json.hpp"
#include "../../Utility.h"
#include "../ModioC.h"

extern "C"
{
  void modioInitLogo(ModioLogo* logo, nlohmann::json logo_json);
  void modioFreeLogo(ModioLogo* logo);
}

#endif
