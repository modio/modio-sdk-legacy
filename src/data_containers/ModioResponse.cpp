#include "data_containers/ModioResponse.h"

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

    response->cursor_id = -1;
    if(modio::hasKey(response_json,"cursor_id"))
    {
      response->cursor_id = response_json["cursor_id"];
    }
    response->prev_id = -1;
    if(modio::hasKey(response_json,"prev_id"))
    {
      response->prev_id = response_json["prev_id"];
    }
    response->next_id = -1;
    if(modio::hasKey(response_json,"next_id"))
    {
      response->next_id = response_json["next_id"];
    }
    response->result_count = -1;
    if(modio::hasKey(response_json,"result_count"))
    {
      response->result_count = response_json["result_count"];
    }
  }

  void modioFreeResponse(ModioResponse* response)
  {
    delete response;
  }
}
