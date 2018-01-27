#include "c++/ModIOInstance.h"

namespace modio
{
  void Instance::subscribeMod(u32 mod_id, const std::function<void(const modio::Response& response, const modio::Mod& mod)>& callback)
  {
    const struct SubscribeModCall* subscribe_mod_call = new SubscribeModCall{callback};
    subscribe_mod_calls[this->current_call_id] = (SubscribeModCall*)subscribe_mod_call;

    modioSubscribeMod((void*)new u32(this->current_call_id), mod_id, &onSubscribeMod);

    this->current_call_id++;
  }

  void Instance::unsubscribeMod(u32 mod_id, const std::function<void(const modio::Response& response)>& callback)
  {
    const struct UnsubscribeModCall* unsubscribe_mod_call = new UnsubscribeModCall{callback};
    unsubscribe_mod_calls[this->current_call_id] = (UnsubscribeModCall*)unsubscribe_mod_call;

    modioUnsubscribeMod((void*)new u32(this->current_call_id), mod_id, &onUnsubscribeMod);

    this->current_call_id++;
  }
}
