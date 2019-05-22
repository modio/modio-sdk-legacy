#include "c++/ModIOInstance.h"

namespace modio
{
std::map<u32, GenericCall *> galaxy_auth_calls;
std::map<u32, GenericCall *> steam_auth_calls;
std::map<u32, GenericCall *> steam_auth_encoded_calls;
std::map<u32, GenericCall *> link_external_account_calls;

void onGalaxyAuth(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;

  response.initialize(modio_response);

  galaxy_auth_calls[call_id]->callback((const modio::Response &)response);

  delete (u32 *)object;
  delete galaxy_auth_calls[call_id];
  galaxy_auth_calls.erase(call_id);
}

void onSteamAuth(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;

  response.initialize(modio_response);

  steam_auth_calls[call_id]->callback((const modio::Response &)response);

  delete (u32 *)object;
  delete steam_auth_calls[call_id];
  steam_auth_calls.erase(call_id);
}

void onSteamAuthEncoded(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;

  response.initialize(modio_response);

  steam_auth_encoded_calls[call_id]->callback((const modio::Response &)response);

  delete (u32 *)object;
  delete steam_auth_encoded_calls[call_id];
  steam_auth_encoded_calls.erase(call_id);
}

void onLinkExternalAccount(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;

  response.initialize(modio_response);

  link_external_account_calls[call_id]->callback((const modio::Response &)response);

  delete (u32 *)object;
  delete link_external_account_calls[call_id];
  link_external_account_calls.erase(call_id);
}

void clearExternalAuthenticationRequestCalls()
{
  for (auto galaxy_auth_call : galaxy_auth_calls)
    delete galaxy_auth_call.second;
  galaxy_auth_calls.clear();

  for (auto steam_auth_call : steam_auth_calls)
    delete steam_auth_call.second;
  steam_auth_calls.clear();

  for (auto steam_auth_encoded_call : steam_auth_encoded_calls)
    delete steam_auth_encoded_call.second;
  steam_auth_encoded_calls.clear();

  for (auto link_external_account_call : link_external_account_calls)
    delete link_external_account_call.second;
  link_external_account_calls.clear();
}
} // namespace modio
