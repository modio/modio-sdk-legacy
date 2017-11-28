#include "instance_data_containers/Tag.h"

namespace modio
{
  void Tag::initialize(ModioTag modio_tag)
  {
    this->date_added = modio_tag.date_added;
    this->name = modio_tag.name;
  }
}
