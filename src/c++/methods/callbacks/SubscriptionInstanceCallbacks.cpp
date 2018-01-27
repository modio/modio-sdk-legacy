#include "c++/ModIOInstance.h"

namespace modio
{
  std::map<u32, SubscribeModCall*> subscribe_mod_calls;
  std::map<u32, UnsubscribeModCall*> unsubscribe_mod_calls;

  void onSubscribeMod(void* object, ModioResponse modio_response, ModioMod mod)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    modio::Mod modio_mod;

    if(modio_response.code == 201)
    {
      modio_mod.initialize(mod);
    }

    subscribe_mod_calls[call_id]->callback((const Response&)response, modio_mod);

    delete (u32*)object;
    delete subscribe_mod_calls[call_id];
    subscribe_mod_calls.erase(call_id);
  }

  void onUnsubscribeMod(void* object, ModioResponse modio_response)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    unsubscribe_mod_calls[call_id]->callback((const Response&)response);

    delete (u32*)object;
    delete unsubscribe_mod_calls[call_id];
    unsubscribe_mod_calls.erase(call_id);
  }
}
