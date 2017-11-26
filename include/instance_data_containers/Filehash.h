#ifndef MODIO_FILEHASH_H
#define MODIO_FILEHASH_H

#include "data_containers/ModioFilehash.h"
#include "Globals.h"

namespace modio
{
  class Filehash
  {
  public:
    std::string md5;

    void initialize(ModioFilehash filehash);
  };
}

#endif
