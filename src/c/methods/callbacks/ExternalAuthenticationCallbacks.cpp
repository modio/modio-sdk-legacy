#include "c/methods/callbacks/ExternalAuthenticationCallbacks.h"

#include "ModUtility.h"
#include "Utility.h" // for hasKey
#include "c/schemas/ModioTerms.h"

std::map< u32,GenericRequestParams* > galaxy_auth_params;
std::map< u32,GenericRequestParams* > oculus_auth_params;
std::map< u32,GenericRequestParams* > steam_auth_params;
std::map< u32,GenericRequestParams* > steam_auth_encoded_params;
std::map< u32,GenericRequestParams* > link_external_account_params;
std::map< u32, TermsParams* > get_terms_params;

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
      modio::writeLogLine("Authenticated through oculus!", MODIO_DEBUGLEVEL_LOG);
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

void modioOnOculusAuth(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  modio::writeLogLine("Oculus auth encoded returned.", MODIO_DEBUGLEVEL_LOG);

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

  oculus_auth_params[call_number]->callback(oculus_auth_params[call_number]->object, response);

  delete oculus_auth_params[call_number];
  oculus_auth_params.erase(call_number);

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
  modio::writeLogLine("Steam auth encoded returned.", MODIO_DEBUGLEVEL_LOG);

  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;
  
  modio::writeLogLine("Auth encoded response retrieved.", MODIO_DEBUGLEVEL_LOG);

  if (response.code == 200)
  {
    modio::writeLogLine("Auth encoded returned successfully.", MODIO_DEBUGLEVEL_LOG);
    std::string access_token = "";
    if (modio::hasKey(response_json, "access_token"))
    {
      modio::writeLogLine("Authenticating user...", MODIO_DEBUGLEVEL_LOG);
      modio::updateAuthenticatedUser(response_json["access_token"]);
      modio::writeLogLine("User authenticated!", MODIO_DEBUGLEVEL_LOG);
    }
    else
    {
      modio::writeLogLine("Could not retreive access token from server.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  modio::writeLogLine("Cleaning up...", MODIO_DEBUGLEVEL_LOG);
  steam_auth_encoded_params[call_number]->callback(steam_auth_encoded_params[call_number]->object, response);

  delete steam_auth_encoded_params[call_number];
  steam_auth_encoded_params.erase(call_number);

  modioFreeResponse(&response);
  modio::writeLogLine("On auth encoded finished", MODIO_DEBUGLEVEL_LOG);
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

void modioOnGetTerms(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioTerms terms;
  ModioTerms* result = nullptr;

  TermsParams* params = get_terms_params[call_number];

  if(response_code == 200)
  {
    // Don't add the call to the cache if it came from the cache
    if(!params->is_cache)
    {
      modio::addCallToCache(params->url, response_json);
    }
    result = &terms;
    modioInitTerms(result, response_json);
  }
  
  for(int i = 0; i < params->callbacks.size(); ++i)
  {
    params->callbacks[i](params->objects[i], response, &terms);
  }

  delete params;
  get_terms_params.erase(call_number);

  if(response_code == 200)
  {
    modioFreeResponse(&response);
  }
}

void clearExternalAuthenticationCallbackParams()
{
  for (auto& galaxy_auth_param : galaxy_auth_params)
    delete galaxy_auth_param.second;
  galaxy_auth_params.clear();

  for (auto& steam_auth_param : steam_auth_params)
    delete steam_auth_param.second;
  steam_auth_params.clear();

  for (auto& steam_auth_encoded_param : steam_auth_encoded_params)
    delete steam_auth_encoded_param.second;
  steam_auth_encoded_params.clear();

  for (auto& link_external_account_param : link_external_account_params)
    delete link_external_account_param.second;
  link_external_account_params.clear();

  for (auto& terms_param : get_terms_params)
    delete terms_param.second;
  get_terms_params.clear();
}
