#include "c/methods/SubscriptionMethods.h"

extern "C"
{
  void modioSubscribeToMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response, ModioMod mod))
  {
    std::map<std::string, std::string> data;

    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    subscribe_to_mod_callbacks[call_number] = new SubscribeToModParams;
    subscribe_to_mod_callbacks[call_number]->callback = callback;
    subscribe_to_mod_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/subscribe";

    modio::curlwrapper::post(call_number, url, headers, data, &modioOnSubscribeToMod);
  }

  void modioUnsubscribeFromMod(void* object, u32 mod_id, void (*callback)(void* object, ModioResponse response))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    unsubscribe_from_mod_callbacks[call_number] = new UnsubscribeFromModParams;
    unsubscribe_from_mod_callbacks[call_number]->callback = callback;
    unsubscribe_from_mod_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/subscribe";

    modio::curlwrapper::deleteCall(call_number, url, headers, &modioOnUnsubscribeFromMod);
  }
}
