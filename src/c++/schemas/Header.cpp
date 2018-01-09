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
}
