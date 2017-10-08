#ifndef MODIO_MEDIA_H
#define MODIO_MEDIA_H

#include "dependencies/json/json.hpp"
#include "data_containers/Image.h"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

namespace modio
{
  class Media
  {
  public:
    Media(json image_json);
    ~Media();
    vector<string> youtube;
    vector<string> sketchfab;
    vector<Image*> images;
  };
}

#endif
