#include "c++/ModIOInstance.h"

namespace modio
{

void Instance::galaxyAuth(const std::string &appdata, const std::function<void(const modio::Response &)> &callback)
{
  const struct GenericCall *galaxy_auth_call = new GenericCall{callback};
  galaxy_auth_calls[this->current_call_id] = (GenericCall *)galaxy_auth_call;

  modioGalaxyAuth((void *)new u32(this->current_call_id), (char *)appdata.c_str(), &onGalaxyAuth);

  this->current_call_id++;
}

void Instance::steamAuth(const unsigned char* rgubTicket, u32 cubTicket, const std::function<void(const modio::Response &)> &callback)
{
  const struct GenericCall *steam_auth_call = new GenericCall{callback};
  steam_auth_calls[this->current_call_id] = (GenericCall *)steam_auth_call;

  modioSteamAuth((void *)new u32(this->current_call_id), (unsigned char*)rgubTicket, cubTicket, &onSteamAuth);

  this->current_call_id++;
}

void Instance::steamAuthEncoded(const std::string &base64_ticket, const std::function<void(const modio::Response &)> &callback)
{
  const struct GenericCall *steam_auth_encoded_call = new GenericCall{callback};
  steam_auth_encoded_calls[this->current_call_id] = (GenericCall *)steam_auth_encoded_call;

  modioSteamAuthEncoded((void *)new u32(this->current_call_id), (char *)base64_ticket.c_str(), &onSteamAuthEncoded);

  this->current_call_id++;
}

void Instance::linkExternalAccount(u32 service, const std::string &service_id, const std::string &email, const std::function<void(const modio::Response &)> &callback)
{
  const struct GenericCall *link_external_account_call = new GenericCall{callback};
  link_external_account_calls[this->current_call_id] = (GenericCall *)link_external_account_call;

  modioLinkExternalAccount((void *)new u32(this->current_call_id), service, (char *)service_id.c_str(), (char *)email.c_str(), &onLinkExternalAccount);

  this->current_call_id++;
}

} // namespace modio
