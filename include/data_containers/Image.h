#ifndef MODIO_IMAGE_H
#define MODIO_IMAGE_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

namespace modio
{
  class Image
  {
  public:
    Image(json image_json);
    string full;
    string thumbnail;
    string filename;
  };
}

#endif
