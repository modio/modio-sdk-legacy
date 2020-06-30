#include "c++/schemas/Error.h"
#include "c/ModioC.h"                      // for ModioError
#include "dependencies/nlohmann/json.hpp"  // for json

namespace modio
{
void Error::initialize(ModioError modio_error)
{
  code = modio_error.code;
  error_ref = modio_error.error_ref;
  if (modio_error.message)
    message = modio_error.message;
  errors.resize(modio_error.errors_array_size);
  for (u32 i = 0; i < modio_error.errors_array_size; i++)
  {
    errors[i] = modio_error.errors_array[i];
  }
}

nlohmann::json toJson(Error &error)
{
  nlohmann::json error_json;

  error_json["code"] = error.code;
  error_json["error_ref"] = error.error_ref;
  error_json["message"] = error.message;

  nlohmann::json errors_json;

  for (u32 i = 0; i<error.errors.size(); i++)
  {
    errors_json.push_back(error.errors[i]);
  }

  error_json["errors"] = errors_json;

  return error_json;
}
} // namespace modio
