#ifndef MODWORKS_MEDIA
#define MODWORKS_MEDIA

#include "dependencies/json/json.hpp"
#include "data_containers/Image.h"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

namespace modworks
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
