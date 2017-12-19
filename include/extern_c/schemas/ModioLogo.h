#ifndef MODIO_MODIOLOGO_H
#define MODIO_MODIOLOGO_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using json = nlohmann::json;

extern "C"
{
  struct ModioLogo
  {
    char* filename;
    char* original;
    char* thumb_320x180;
    char* thumb_640x360;
    char* thumb_1280x720;
  };

  void modioInitLogo(ModioLogo* logo, json logo_json);
  void modioFreeLogo(ModioLogo* logo);
}

#endif
