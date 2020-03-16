#include "c/schemas/ModioResponse.h"
#include "Utility.h"                // for hasKey
#include "c/ModioC.h"               // for ModioDownload
#include "c/schemas/ModioError.h" // for modioInitError ...

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

  void modioInitResponseCpp(ModioResponse* modio_response, modio::Response* response)
  {
    modio_response->code = response->code;
    modio_response->result_cached = response->result_cached;
    modio_response->result_count = response->result_count;
    modio_response->result_limit = response->result_limit;
    modio_response->result_offset = response->result_offset;
    modio_response->result_total = response->result_total;

    modioInitErrorCpp(&(modio_response->error), &(response->error));
  }

  void modioFreeResponse(ModioResponse* response)
  {
    if(response)
    {
      modioFreeError(&(response->error));
    }
  }
}
