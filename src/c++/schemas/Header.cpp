#include "c++/schemas/Header.h"
#include "c/ModioC.h"                      // for ModioHeader
#include "dependencies/nlohmann/json.hpp"  // for json

namespace modio
{
void Header::initialize(ModioHeader modio_header)
{
  if (modio_header.filename)
    filename = modio_header.filename;
  if (modio_header.original)
    original = modio_header.original;
}

nlohmann::json toJson(Header &header)
{
  nlohmann::json header_json;

  header_json["filename"] = header.filename;
  header_json["original"] = header.original;

  return header_json;
}
} // namespace modio
