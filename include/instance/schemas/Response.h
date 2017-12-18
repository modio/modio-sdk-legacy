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
    u32 result_count;
    u32 result_limit;
    i32 result_offset;

    modio::Error error;

    void initialize(ModioResponse response);
  };
}

#endif
