#include "c++/schemas/Response.h"

namespace modio
{
  void Response::initialize(ModioResponse modio_response)
  {
    this->code = modio_response.code;
    this->result_count = modio_response.result_count;
    this->result_limit = modio_response.result_limit;
    this->result_offset = modio_response.result_offset;
    this->error.initialize(modio_response.error);
  }
}
