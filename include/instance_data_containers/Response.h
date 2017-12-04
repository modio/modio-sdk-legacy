#ifndef MODIO_RESPONSE_H
#define MODIO_RESPONSE_H

#include "Globals.h"
#include "data_containers/ModioResponse.h"
#include "instance_data_containers/Error.h"

namespace modio
{
  class Response
  {
  public:
    u32 code;
    u32 cursor_id;
    u32 prev_id;
    u32 next_id;
    u32 result_count;
    modio::Error error;

    void initialize(ModioResponse response);
  };
}

#endif
