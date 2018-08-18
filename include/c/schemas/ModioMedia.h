#ifndef MODIO_MODIOMEDIA_H
#define MODIO_MODIOMEDIA_H

#include "../../dependencies/json/json.hpp"
#include "../../Utility.h"
#include "../ModioC.h"
#include "ModioImage.h"

extern "C"
{
  void modioInitMedia(ModioMedia* media, nlohmann::json media_json);
  void modioFreeMedia(ModioMedia* media);
}

#endif
