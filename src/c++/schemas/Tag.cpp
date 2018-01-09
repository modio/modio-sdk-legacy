#include "c++/schemas/Tag.h"

namespace modio
{
  void Tag::initialize(ModioTag modio_tag)
  {
    this->date_added = modio_tag.date_added;
    if(modio_tag.name)
      this->name = modio_tag.name;
  }
}
