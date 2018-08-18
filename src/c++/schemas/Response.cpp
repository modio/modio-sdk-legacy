#include "c++/schemas/Response.h"

namespace modio
{
  void Response::initialize(ModioResponse modio_response)
  {
    this->code = modio_response.code;
    this->result_count = modio_response.result_count;
    this->result_limit = modio_response.result_limit;
    this->result_offset = modio_response.result_offset;
    this->result_cached = modio_response.result_cached;
    this->error.initialize(modio_response.error);
  }

  nlohmann::json Response::toJson()
  {
    nlohmann::json response_json;

    response_json["code"] = this->code;
    response_json["result_count"] = this->result_count;
    response_json["result_limit"] = this->result_limit;
    response_json["result_offset"] = this->result_offset;
    response_json["result_cached"] = this->result_cached;
    response_json["error"] = this->error.toJson();

    return response_json;
  }
}
