#ifndef MODIO_MODIOIMAGE_H
#define MODIO_MODIOIMAGE_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "extern_c/ModioC.h"

using json = nlohmann::json;

extern "C"
{
  void modioInitImage(ModioImage* image, json image_json);
  void modioFreeImage(ModioImage* image);
}

#endif
