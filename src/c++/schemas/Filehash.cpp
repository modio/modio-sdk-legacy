#include "c++/schemas/Filehash.h"

namespace modio
{
  void Filehash::initialize(ModioFilehash modio_filehash)
  {
    if(modio_filehash.md5)
      this->md5 = modio_filehash.md5;
  }

  nlohmann::json Filehash::toJson()
  {
    nlohmann::json filehash_json;

    filehash_json["md5"] = this->md5;

    return filehash_json;
  }
}
