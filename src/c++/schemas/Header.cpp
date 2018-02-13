#include "c++/schemas/Header.h"

namespace modio
{
  void Header::initialize(ModioHeader modio_header)
  {
    if(modio_header.filename)
      this->filename = modio_header.filename;
    if(modio_header.original)
      this->original = modio_header.original;
  }

  json Header::toJson()
  {
    json header_json;

    header_json["filename"] = this->filename;
    header_json["original"] = this->original;

    return header_json;
  }
}
