#ifndef MODIO_IMAGE_H
#define MODIO_IMAGE_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

namespace modio
{
  struct Image
  {
    string full;
    string thumbnail;
    string filename;
  };

  void initImage(Image* image, json image_json);
  void freeImage(Image* image);
}

#endif
