#include "instance_data_containers/Filehash.h"

namespace modio
{
  void Filehash::initialize(ModioFilehash modio_filehash)
  {
    this->md5 = modio_filehash.md5;
  }
}
