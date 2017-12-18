#ifndef MODIO_MODIORESPONSE_H
#define MODIO_MODIORESPONSE_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "extern_c/schemas/ModioError.h"

using json = nlohmann::json;

extern "C"
{
  struct ModioResponse
  {
    u32 code;
    u32 result_count;
    u32 result_limit;
    i32 result_offset;
    ModioError error;
  };

  void modioInitResponse(ModioResponse* response, json response_json);
  void modioFreeResponse(ModioResponse* response);
}

#endif
