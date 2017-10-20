#ifndef MODIO_IMAGE_H
#define MODIO_IMAGE_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct ModioImage
  {
    char* full;
    char* thumbnail;
    char* filename;
  };

  void modioInitImage(ModioImage* image, json image_json);
  void modioFreeImage(ModioImage* image);
}

#endif
