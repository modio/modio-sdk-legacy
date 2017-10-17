#ifndef MODIO_META_CURSOR_H
#define MODIO_META_CURSOR_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct ModioMetaCursor
  {
    int current;
    int prev;
    int next;
    int count;
  };

  void modioInitMetaCursor(ModioMetaCursor* response, json image_json);
  void modioFreeMetaCursor(ModioMetaCursor* response);
}

#endif
