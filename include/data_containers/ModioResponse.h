#ifndef MODIO_MODIORESPONSE_H
#define MODIO_MODIORESPONSE_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "data_containers/ModioError.h"

using json = nlohmann::json;

extern "C"
{
  struct ModioResponse
  {
    u32 code;
    u32 cursor_id;
    u32 prev_id;
    u32 next_id;
    u32 result_count;
    ModioError error;
  };

  void modioInitResponse(ModioResponse* response, json response_json);
  void modioFreeResponse(ModioResponse* response);
}

#endif
