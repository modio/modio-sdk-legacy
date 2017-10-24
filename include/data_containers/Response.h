#ifndef MODIO_RESPONSE_H
#define MODIO_RESPONSE_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "data_containers/Error.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct ModioResponse
  {
    int code;
    ModioError* error;
    int cursor_id;
    int prev_id;
    int next_id;
    int result_count;
  };

  void modioInitResponse(ModioResponse* response, json response_json);
  void modioFreeResponse(ModioResponse* response);
}

#endif
