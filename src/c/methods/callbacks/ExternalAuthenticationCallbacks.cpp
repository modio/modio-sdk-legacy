#include "c/methods/callbacks/AuthenticationCallbacks.h"

std::map< u32,GenericRequestParams* > galaxy_auth_params;
std::map< u32,GenericRequestParams* > steam_auth_params;
std::map< u32,GenericRequestParams* > link_external_account_params;

void modioOnGalaxyAuth(u32 call_number, u32 response_code, nlohmann::json response_json)
{

}

void modioOnSteamAuth(u32 call_number, u32 response_code, nlohmann::json response_json)
{

}

void modioOnLinkExternalAccount(u32 call_number, u32 response_code, nlohmann::json response_json)
{

}

void clearExternalAuthenticationCallbackParams()
{
  for (auto galaxy_auth_param : galaxy_auth_params)
    delete galaxy_auth_param.second;
  galaxy_auth_params.clear();

  for (auto steam_auth_param : steam_auth_params)
    delete steam_auth_param.second;
  steam_auth_params.clear();

  for (auto link_external_account_param : link_external_account_params)
    delete link_external_account_param.second;
  link_external_account_params.clear();
}