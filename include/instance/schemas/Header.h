#ifndef MODIO_HEADER_H
#define MODIO_HEADER_H

#include "extern_c/schemas/ModioHeader.h"
#include "Globals.h"
#include "Utility.h"

namespace modio
{
  class Header
  {
  public:
    std::string filename;
    std::string original;

    void initialize(ModioHeader Header);
  };
}

#endif
