#ifndef MODIO_RESPONSE_H
#define MODIO_RESPONSE_H

#include "data_containers/ModioResponse.h"
#include "Globals.h"
#include "instance_data_containers/Error.h"

namespace modio
{
  class Response
  {
  public:
    int code;
    int cursor_id;
    int prev_id;
    int next_id;
    int result_count;
    modio::Error error;

    void initialize(ModioResponse response);
  };
}

#endif
