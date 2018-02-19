#include "c++/ModIOInstance.h"

namespace modio
{
  std::map<u32, InstallModCall*> install_mod_calls;

  void onInstallModfile(void* object, ModioResponse modio_response)
  {
    u32 call_id = *((u32*)object);
    modio::Response response;
    response.initialize(modio_response);
    install_mod_calls[call_id]->callback(response);
    delete (u32*)object;
    delete install_mod_calls[call_id];
    install_mod_calls.erase(call_id);
  }
}
