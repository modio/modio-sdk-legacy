#ifndef MODWORKS_IMAGE
#define MODWORKS_IMAGE

#include "dependencies/json/json.hpp"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

namespace modworks
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
