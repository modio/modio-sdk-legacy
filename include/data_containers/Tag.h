#ifndef MODIO_TAG_H
#define MODIO_TAG_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

namespace modio
{
  class Tag
  {
  public:
    Tag(json tag_json);
    int game;
    int mod;
    int date;
    string tag;
  };
}

#endif
