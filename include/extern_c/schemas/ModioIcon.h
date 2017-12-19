#ifndef MODIO_MODIOICON_H
#define MODIO_MODIOICON_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using json = nlohmann::json;

extern "C"
{
  struct ModioIcon
  {
    char* filename;
    char* original;
    char* thumb_64x64;
    char* thumb_128x128;
    char* thumb_256x256;
  };

  void modioInitIcon(ModioIcon* icon, json icon_json);
  void modioFreeIcon(ModioIcon* icon);
}

#endif
