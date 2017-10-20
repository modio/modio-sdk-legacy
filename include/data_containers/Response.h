#ifndef MODIO_RESPONSE_H
#define MODIO_RESPONSE_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "data_containers/Error.h"
#include "data_containers/Cursor.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct ModioResponse
  {
    int code;
    ModioError* error;
    ModioCursor* cursor;
  };

  void modioInitResponse(ModioResponse* response, json response_json);
  void modioFreeResponse(ModioResponse* response);
}

#endif
