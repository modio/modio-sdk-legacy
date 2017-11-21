#include "ModIOInstance.h"

namespace modio
{
  Instance::Instance(u32 id, const std::string& guid)
  {
    modioInit(id, (char*)guid.c_str());
  }
}
