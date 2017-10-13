#ifndef MODIO_MEDIA_H
#define MODIO_MEDIA_H

#include "dependencies/json/json.hpp"
#include "data_containers/Image.h"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

namespace modio
{
  struct Media
  {
    vector<string> youtube;
    vector<string> sketchfab;
    vector<Image*> images;
  };

  void initMedia(Media* media, json media_json);
  void freeMedia(Media* media);
}

#endif
