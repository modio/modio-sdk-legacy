#ifndef MODIO_TAG_H
#define MODIO_TAG_H

#include "Globals.h"
#include "data_containers/ModioTag.h"

namespace modio
{
  class Tag
  {
  public:
    u32 date_added;
    std::string name;

    void initialize(ModioTag tag);
  };
}

#endif
