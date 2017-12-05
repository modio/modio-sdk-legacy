#ifndef MODIO_MODIOTAG_H
#define MODIO_MODIOTAG_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using json = nlohmann::json;

extern "C"
{
  struct ModioTag
  {
    u32 date_added;
    char* name;
  };

  void modioInitTag(ModioTag* tag, json tag_json);
  void modioFreeTag(ModioTag* tag);
}

#endif
