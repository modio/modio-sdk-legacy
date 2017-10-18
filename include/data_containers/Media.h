#ifndef MODIO_MEDIA_H
#define MODIO_MEDIA_H

#include "dependencies/json/json.hpp"
#include "data_containers/Image.h"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct ModioMedia
  {
    char** youtube_array;
    int youtube_size;
    char** sketchfab_array;
    int sketchfab_size;
    ModioImage** images_array;
    int images_size;
  };

  void modioInitMedia(ModioMedia* media, json media_json);
  void modioFreeMedia(ModioMedia* media);
}

#endif
