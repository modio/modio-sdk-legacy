#ifndef MODIO_IMAGE_H
#define MODIO_IMAGE_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using json = nlohmann::json;

extern "C"
{
  struct ModioImage
  {
    char* filename;
    char* full;
    char* thumb_1280x720;
    char* thumb_640x360;
    char* thumb_320x180;
  };

  void modioInitImage(ModioImage* image, json image_json);
  void modioFreeImage(ModioImage* image);
}

#endif
