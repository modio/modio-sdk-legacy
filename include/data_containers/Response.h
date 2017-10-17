#ifndef MODIO_RESPONSE_H
#define MODIO_RESPONSE_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct ModioResponse
  {
    int code;
    ModioError* error;
    ModioMetaCursor* meta_cursor;
  };

  void modioInitResponse(ModioResponse* response, json image_json);
  void modioFreeResponse(ModioResponse* response);
}

#endif
