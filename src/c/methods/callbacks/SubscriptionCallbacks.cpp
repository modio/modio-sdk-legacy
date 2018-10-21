#include "c/methods/callbacks/SubscriptionCallbacks.h"

std::map<u32, SubscribeToModParams *> subscribe_to_mod_callbacks;
std::map<u32, UnsubscribeFromModParams *> unsubscribe_from_mod_callbacks;

void modioOnSubscribeToMod(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioMod mod;
  modioInitMod(&mod, response_json);

  subscribe_to_mod_callbacks[call_number]->callback(subscribe_to_mod_callbacks[call_number]->object, response, mod);

  delete subscribe_to_mod_callbacks[call_number];
  subscribe_to_mod_callbacks.erase(call_number);

  modioFreeResponse(&response);

  modioFreeMod(&mod);
}

void modioOnUnsubscribeFromMod(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  unsubscribe_from_mod_callbacks[call_number]->callback(unsubscribe_from_mod_callbacks[call_number]->object, response);

  delete unsubscribe_from_mod_callbacks[call_number];
  unsubscribe_from_mod_callbacks.erase(call_number);
  
  modioFreeResponse(&response);
}

void clearSubscriptionCallbackParams()
{
  for (auto subscribe_to_mod_callback : subscribe_to_mod_callbacks)
    delete subscribe_to_mod_callback.second;
  subscribe_to_mod_callbacks.clear();

  for (auto unsubscribe_from_mod_callback : unsubscribe_from_mod_callbacks)
    delete unsubscribe_from_mod_callback.second;
  unsubscribe_from_mod_callbacks.clear();
}