#include "c/methods/SubscriptionMethods.h"

extern "C"
{
  void modioSubscribeToMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioMod mod))
  {
    std::map<std::string, std::string> data;

    u32 call_number = modio::curlwrapper::getCallNumber();

    subscribe_to_mod_callbacks[call_number] = new SubscribeToModParams;
    subscribe_to_mod_callbacks[call_number]->callback = callback;
    subscribe_to_mod_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/subscribe";

    modio::curlwrapper::post(call_number, url, modio::getHeaders(), data, &modioOnSubscribeToMod);
  }

  void modioUnsubscribeFromMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response))
  {
    std::map<std::string, std::string> data;
    u32 call_number = modio::curlwrapper::getCallNumber();

    unsubscribe_from_mod_callbacks[call_number] = new GenericRequestParams;
    unsubscribe_from_mod_callbacks[call_number]->callback = callback;
    unsubscribe_from_mod_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/subscribe";

    modio::curlwrapper::deleteCall(call_number, url, modio::getHeaders(), data, &modioOnUnsubscribeFromMod);
  }
}
