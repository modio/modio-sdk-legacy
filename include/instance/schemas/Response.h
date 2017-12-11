#ifndef MODIO_RESPONSE_H
#define MODIO_RESPONSE_H

#include "Globals.h"
#include "extern_c/schemas/ModioResponse.h"
#include "instance/schemas/Error.h"

namespace modio
{
  class Response
  {
  public:
    u32 code;
    i32 cursor_id;
    i32 prev_id;
    i32 next_id;
    u32 result_count;
    modio::Error error;

    void initialize(ModioResponse response);
  };
}

#endif
