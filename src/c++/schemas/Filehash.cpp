#include "c++/schemas/Filehash.h"
#include "c/ModioC.h"                      // for ModioFilehash
#include "dependencies/nlohmann/json.hpp"  // for json

namespace modio
{
void Filehash::initialize(ModioFilehash modio_filehash)
{
  if (modio_filehash.md5)
    md5 = modio_filehash.md5;
}

nlohmann::json toJson(Filehash &filehash)
{
  nlohmann::json filehash_json;

  filehash_json["md5"] = filehash.md5;

  return filehash_json;
}
} // namespace modio
