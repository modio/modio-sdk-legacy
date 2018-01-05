#ifndef MODIO_MODIOICON_H
#define MODIO_MODIOICON_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "extern_c/ModioC.h"

using json = nlohmann::json;

extern "C"
{
  void modioInitIcon(ModioIcon* icon, json icon_json);
  void modioFreeIcon(ModioIcon* icon);
}

#endif
