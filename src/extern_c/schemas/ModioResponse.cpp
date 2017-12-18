#include "extern_c/schemas/ModioResponse.h"

extern "C"
{
  void modioInitResponse(ModioResponse* response, json response_json)
  {
    response->code = -1;

    if(modio::hasKey(response_json, "error"))
    {
      modioInitError(&(response->error),response_json["error"]);
    }else
    {
      json empty_json;
      modioInitError(&(response->error),empty_json);
    }

    response->result_count = 0;
    if(modio::hasKey(response_json,"result_count"))
    {
      response->result_count = response_json["result_count"];
    }

    response->result_limit = 0;
    if(modio::hasKey(response_json,"result_limit"))
    {
      response->result_limit = response_json["result_limit"];
    }

    response->result_offset = -1;
    if(modio::hasKey(response_json,"result_offset"))
    {
      response->result_offset = response_json["result_offset"];
    }


  }

  void modioFreeResponse(ModioResponse* response)
  {
    delete response;
  }
}
