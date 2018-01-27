#include "c/methods/callbacks/SubscriptionCallbacks.h"

std::map< u32, SubscribeModParams* > subscribe_mod_callbacks;
std::map< u32, UnsubscribeModParams* > unsubscribe_mod_callbacks;

void modioOnSubscribeMod(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioMod mod;
  modioInitMod(&mod, response_json);

  subscribe_mod_callbacks[call_number]->callback(subscribe_mod_callbacks[call_number]->object, response, mod);

  delete subscribe_mod_callbacks[call_number];
  subscribe_mod_callbacks.erase(call_number);

  modioFreeResponse(&response);
  modioFreeMod(&mod);
}

void modioOnUnsubscribeMod(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  unsubscribe_mod_callbacks[call_number]->callback(unsubscribe_mod_callbacks[call_number]->object, response);

  delete unsubscribe_mod_callbacks[call_number];
  unsubscribe_mod_callbacks.erase(call_number);
}
