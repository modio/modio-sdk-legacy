#ifndef MODIO_TAG_H
#define MODIO_TAG_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using json = nlohmann::json;

extern "C"
{
  struct ModioTag
  {
    int game;
    int mod;
    int date;
    char* tag;
  };

  void modioInitTag(ModioTag* tag, json tag_json);
  void modioFreeTag(ModioTag* tag);
}

#endif
