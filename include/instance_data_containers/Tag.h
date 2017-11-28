#ifndef MODIO_TAG_H
#define MODIO_TAG_H

#include "data_containers/ModioTag.h"
#include "Globals.h"

namespace modio
{
  class Tag
  {
  public:
    int date_added;
    std::string name;

    void initialize(ModioTag tag);
  };
}

#endif
