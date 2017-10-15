#ifndef MODIO_TAG_H
#define MODIO_TAG_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct Tag
  {
    int game;
    int mod;
    int date;
    string tag;
  };

  void initTag(Tag* tag, json tag_json);
  void freeTag(Tag* tag);
}

#endif
