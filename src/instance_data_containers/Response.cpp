#include "instance_data_containers/Response.h"

namespace modio
{
  void Response::initialize(ModioResponse modio_response)
  {
    this->code = modio_response.code;
    this->cursor_id = modio_response.cursor_id;
    this->prev_id = modio_response.prev_id;
    this->next_id = modio_response.next_id;
    this->result_count = modio_response.result_count;
    this->error.initialize(modio_response.error);
  }
}
