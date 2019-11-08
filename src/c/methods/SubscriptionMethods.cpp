#include "c/methods/SubscriptionMethods.h"

extern "C"
{
  void modioSubscribeToMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioMod mod))
  {
    std::map<std::string, std::string> data;

    u32 call_number = modio::curlwrapper::getCallNumber();

    subscribe_to_mod_callbacks[call_number] = new SubscribeToModParams;
    subscribe_to_mod_callbacks[call_number]->object = object;
    subscribe_to_mod_callbacks[call_number]->mod_id = mod_id;
    subscribe_to_mod_callbacks[call_number]->callback = callback;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/subscribe";

    modio::curlwrapper::post(call_number, url, modio::getHeaders(), data, &modioOnSubscribeToMod);
  }

  void modioUnsubscribeFromMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response))
  {
    std::map<std::string, std::string> data;
    u32 call_number = modio::curlwrapper::getCallNumber();

    unsubscribe_from_mod_callbacks[call_number] = new UnsubscribeFromModParams;
    unsubscribe_from_mod_callbacks[call_number]->object = object;
    unsubscribe_from_mod_callbacks[call_number]->mod_id = mod_id;
    unsubscribe_from_mod_callbacks[call_number]->callback = callback;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/subscribe";

    modio::curlwrapper::deleteCall(call_number, url, modio::getHeaders(), data, &modioOnUnsubscribeFromMod);
  }

  bool modioIsCurrentUserSubscribed(u32 mod_id)
  {
    if ( modio::current_user_subscriptions.find(mod_id) == modio::current_user_subscriptions.end() )
      return false;
    return true;
  }

  u32 modioGetCurrentUserSubscriptionsCount()
  {
    return (u32)modio::current_user_subscriptions.size();
  }

  void modioGetCurrentUserSubscriptions(u32 *mod_id_array)
  {
    u32 i = 0;
    for(auto current_user_subscription : modio::current_user_subscriptions)
    {
      mod_id_array[i] = current_user_subscription;
      i++;
    }
  }
}
