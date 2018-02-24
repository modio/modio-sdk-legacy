#include "c++/ModIOInstance.h"

namespace modio
{
  Instance::Instance(u32 environment, u32 id, const std::string& guid)
  {
    this->current_call_id = 0;
    modioInit(environment, id, (char*)guid.c_str());
  }

  void Instance::setDebugLevel(u32 debug_level)
  {
    modioSetDebugLevel(debug_level);
  }

  void Instance::sleep(u32 milliseconds)
  {
    modioSleep(milliseconds);
  }

  void Instance::process()
  {
    modioProcess();
  }
}
