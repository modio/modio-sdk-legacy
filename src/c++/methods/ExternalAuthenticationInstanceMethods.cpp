#include "c++/ModIOInstance.h"
#include "ModioUtility.h"
#include "c++/methods/callbacks/ExternalAuthenticationInstanceCallbacks.h"

namespace modio
{

void Instance::galaxyAuth(const std::string &appdata, const std::function<void(const modio::Response &)> &callback)
{
  struct GenericCall *galaxy_auth_call = new GenericCall{callback};
  galaxy_auth_calls[current_call_id] = galaxy_auth_call;

  modioGalaxyAuth((void*)((uintptr_t)current_call_id), appdata.c_str(), &onGalaxyAuth);

  current_call_id++;
}

void Instance::oculusAuth(const std::string &nonce, const std::string &oculus_user_id, const std::string &access_token, const std::string &email, u32 date_expires, const std::function<void(const modio::Response &)> &callback)
{
  struct GenericCall *oculus_auth_call = new GenericCall{callback};
  oculus_auth_calls[current_call_id] = oculus_auth_call;

  char* email_c = NULL;
  if(email != "")
    email_c = (char*)email.c_str();

  modioOculusAuth((void*)((uintptr_t)current_call_id), nonce.c_str(), oculus_user_id.c_str(), access_token.c_str(), email_c, date_expires, &onOculusAuth);

  current_call_id++;
}

void Instance::steamAuth(const unsigned char* rgubTicket, u32 cubTicket, const std::function<void(const modio::Response &)> &callback)
{
  struct GenericCall *steam_auth_call = new GenericCall{callback};
  steam_auth_calls[current_call_id] = steam_auth_call;

  modioSteamAuth((void*)((uintptr_t)current_call_id), rgubTicket, cubTicket, &onSteamAuth);

  current_call_id++;
}

void Instance::steamAuthEncoded(const std::string &base64_ticket, const std::function<void(const modio::Response &)> &callback)
{
  struct GenericCall *steam_auth_encoded_call = new GenericCall{callback};
  steam_auth_encoded_calls[current_call_id] = steam_auth_encoded_call;

  modioSteamAuthEncoded((void*)((uintptr_t)current_call_id), base64_ticket.c_str(), &onSteamAuthEncoded);

  current_call_id++;
}

void Instance::linkExternalAccount(u32 service, const std::string &service_id, const std::string &email, const std::function<void(const modio::Response &)> &callback)
{
  struct GenericCall *link_external_account_call = new GenericCall{callback};
  link_external_account_calls[current_call_id] = link_external_account_call;

  modioLinkExternalAccount((void*)((uintptr_t)current_call_id), service, service_id.c_str(), email.c_str(), &onLinkExternalAccount);

  current_call_id++;
}

} // namespace modio
