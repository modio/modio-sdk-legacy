#include "c/methods/callbacks/AuthenticationCallbacks.h"

std::map< u32,GenericRequestParams* > galaxy_auth_params;
std::map< u32,GenericRequestParams* > steam_auth_params;
std::map< u32,GenericRequestParams* > steam_auth_encoded_params;
std::map< u32,GenericRequestParams* > link_external_account_params;

void modioOnGalaxyAuth(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  if (response.code == 200)
  {
    std::string access_token = "";
    if (modio::hasKey(response_json, "access_token"))
    {
      modio::updateAuthenticatedUser(response_json["access_token"]);
    }
    else
    {
      modio::writeLogLine("Could not retreive access token from server.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  galaxy_auth_params[call_number]->callback(galaxy_auth_params[call_number]->object, response);

  delete galaxy_auth_params[call_number];
  galaxy_auth_params.erase(call_number);

  modioFreeResponse(&response);
}

void modioOnSteamAuth(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  if (response.code == 200)
  {
    std::string access_token = "";
    if (modio::hasKey(response_json, "access_token"))
    {
      modio::updateAuthenticatedUser(response_json["access_token"]);
    }
    else
    {
      modio::writeLogLine("Could not retreive access token from server.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  steam_auth_params[call_number]->callback(steam_auth_params[call_number]->object, response);

  delete steam_auth_params[call_number];
  steam_auth_params.erase(call_number);

  modioFreeResponse(&response);
}

void modioOnSteamAuthEncoded(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  if (response.code == 200)
  {
    std::string access_token = "";
    if (modio::hasKey(response_json, "access_token"))
    {
      modio::updateAuthenticatedUser(response_json["access_token"]);
    }
    else
    {
      modio::writeLogLine("Could not retreive access token from server.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  steam_auth_encoded_params[call_number]->callback(steam_auth_encoded_params[call_number]->object, response);

  delete steam_auth_encoded_params[call_number];
  steam_auth_encoded_params.erase(call_number);

  modioFreeResponse(&response);
}

void modioOnLinkExternalAccount(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  link_external_account_params[call_number]->callback(link_external_account_params[call_number]->object, response);
  delete link_external_account_params[call_number];
  link_external_account_params.erase(call_number);

  modioFreeResponse(&response);
}

void clearExternalAuthenticationCallbackParams()
{
  for (auto galaxy_auth_param : galaxy_auth_params)
    delete galaxy_auth_param.second;
  galaxy_auth_params.clear();

  for (auto steam_auth_param : steam_auth_params)
    delete steam_auth_param.second;
  steam_auth_params.clear();

  for (auto steam_auth_encoded_param : steam_auth_encoded_params)
    delete steam_auth_encoded_param.second;
  steam_auth_encoded_params.clear();

  for (auto link_external_account_param : link_external_account_params)
    delete link_external_account_param.second;
  link_external_account_params.clear();
}