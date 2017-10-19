#ifndef MODIO_CURSOR_H
#define MODIO_CURSOR_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct ModioCursor
  {
    int current;
    int prev;
    int next;
    int count;
  };

  void modioInitCursor(ModioCursor* response, json image_json);
  void modioFreeCursor(ModioCursor* response);
}

#endif
