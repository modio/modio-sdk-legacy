#include "c++/schemas/Response.h"

namespace modio
{
void Response::initialize(ModioResponse modio_response)
{
  this->code = modio_response.code;
  this->result_count = modio_response.result_count;
  this->result_limit = modio_response.result_limit;
  this->result_offset = modio_response.result_offset;
  this->result_total = modio_response.result_total;
  this->result_cached = modio_response.result_cached;
  this->error.initialize(modio_response.error);
}

nlohmann::json toJson(Response &response)
{
  nlohmann::json response_json;

  response_json["code"] = response.code;
  response_json["result_count"] = response.result_count;
  response_json["result_limit"] = response.result_limit;
  response_json["result_offset"] = response.result_offset;
  response_json["result_total"] = response.result_total;
  response_json["result_cached"] = response.result_cached;
  response_json["error"] = modio::toJson(response.error);

  return response_json;
}
} // namespace modio
