#include "data_containers/Response.h"

extern "C"
{
  void modioInitResponse(ModioResponse* response, json response_json)
  {
    response->code = -1;

    response->error = NULL;
    if(modio::hasKey(response_json, "error"))
    {
      response->error = new ModioError;
      modioInitError(response->error,response_json["error"]);
    }

    response->cursor = NULL;
    if(modio::hasKey(response_json, "meta") && modio::hasKey(response_json["meta"], "cursor"))
    {
      response->cursor = new ModioCursor;
      modioInitCursor(response->cursor,response_json["meta"]["cursor"]);
    }
  }

  void modioFreeResponse(ModioResponse* response)
  {
    modioFreeError(response->error);
    modioFreeCursor(response->cursor);
    delete response;
  }
}
