#ifndef MODIO_MODIOTAG_H
#define MODIO_MODIOTAG_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using json = nlohmann::json;

extern "C"
{
  struct ModioTag
  {
    int date_added;
    char* tag;
  };

  void modioInitTag(ModioTag* tag, json tag_json);
  void modioFreeTag(ModioTag* tag);
}

#endif
