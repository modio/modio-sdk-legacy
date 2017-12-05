#ifndef MODIO_MODIOMEDIA_H
#define MODIO_MODIOMEDIA_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "extern_c/schemas/ModioImage.h"

using json = nlohmann::json;

extern "C"
{
  struct ModioMedia
  {
    char** youtube_array;
    u32 youtube_size;
    char** sketchfab_array;
    u32 sketchfab_size;
    ModioImage* images_array;
    u32 images_size;
  };

  void modioInitMedia(ModioMedia* media, json media_json);
  void modioFreeMedia(ModioMedia* media);
}

#endif
