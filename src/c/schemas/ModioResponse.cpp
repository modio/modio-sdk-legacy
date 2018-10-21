#include "c/schemas/ModioResponse.h"

extern "C"
{
  void modioInitResponse(ModioResponse* response, nlohmann::json response_json)
  {
    response->code = 0;
    response->result_cached = false;

    response->result_count = 0;
    if(modio::hasKey(response_json,"result_count"))
      response->result_count = response_json["result_count"];

    response->result_limit = 0;
    if(modio::hasKey(response_json,"result_limit"))
      response->result_limit = response_json["result_limit"];

    response->result_offset = -1;
    if(modio::hasKey(response_json,"result_offset"))
      response->result_offset = response_json["result_offset"];

    response->result_total = 0;
    if(modio::hasKey(response_json,"result_total"))
      response->result_total = response_json["result_total"];

    nlohmann::json error_json;
    if(modio::hasKey(response_json, "error"))
      error_json = response_json["error"];

    modioInitError(&(response->error), error_json);
  }

  void modioFreeResponse(ModioResponse* response)
  {
    if(response)
    {
      modioFreeError(&(response->error));
    }
  }
}
