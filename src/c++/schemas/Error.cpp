#include "c++/schemas/Error.h"

namespace modio
{
  void Error::initialize(ModioError modio_error)
  {
    this->code = modio_error.code;
    if(modio_error.message)
      this->message = modio_error.message;
    this->errors.resize(modio_error.errors_array_size);
    for(u32 i = 0; i < modio_error.errors_array_size; i++)
    {
      this->errors[i] = modio_error.errors_array[i];
    }
  }

  nlohmann::json Error::toJson()
  {
    nlohmann::json error_json;

    error_json["code"] = this->code;
    error_json["message"] = this->message;

    nlohmann::json errors_json;
    for(auto& error : errors)
    {
      errors_json.push_back(error);
    }
    error_json["errors"] = errors_json;

    return error_json;
  }
}
