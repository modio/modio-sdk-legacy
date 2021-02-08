#include <map>
#include <string>
#include "Utility.h"
#include "c/ModioC.h"
#include "dependencies/nlohmann/json.hpp"
#include "wrappers/CurlWrapper.h"
#include "Globals.h"
#include "ModioUtility.h"
#include "c/methods/callbacks/ExternalAuthenticationCallbacks.h"
#include "wrappers/CurlUtility.h"

extern "C"
{
  void modioGalaxyAuth(void* object, char const* appdata, void (*callback)(void* object, ModioResponse response))
  {
    u32 call_number = modio::curlwrapper::getCallNumber();

    galaxy_auth_params[call_number] = new GenericRequestParams;
    galaxy_auth_params[call_number]->callback = callback;
    galaxy_auth_params[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "external/galaxyauth";
    url += "?api_key=" + modio::API_KEY;    

    std::map<std::string, std::string> data;
    data["appdata"] = modio::curlwrapper::dataURLEncode(std::string(appdata));

    modio::curlwrapper::post(call_number, url, modio::getHeadersNoToken(), data, &modioOnGalaxyAuth);
  }

  void modioOculusAuth(void* object, char const* nonce, char const* oculus_user_id, char const* access_token, char const* email, char const* device, u32 date_expires, void (*callback)(void* object, ModioResponse response))
  {
    u32 call_number = modio::curlwrapper::getCallNumber();

    oculus_auth_params[call_number] = new GenericRequestParams;
    oculus_auth_params[call_number]->callback = callback;
    oculus_auth_params[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "external/oculusauth";
    url += "?api_key=" + modio::API_KEY;    

    std::map<std::string, std::string> data;
    data["nonce"] = modio::curlwrapper::dataURLEncode(std::string(nonce));
    data["user_id"] = modio::curlwrapper::dataURLEncode(std::string(oculus_user_id));
    data["access_token"] = modio::curlwrapper::dataURLEncode(std::string(access_token));
    if(email)
      data["email"] = modio::curlwrapper::dataURLEncode(std::string(email));
    if(date_expires != 0)
      data["date_expires"] = modio::curlwrapper::dataURLEncode(modio::toString(date_expires));
    data["device"] = modio::curlwrapper::dataURLEncode(std::string(device));

    modio::curlwrapper::post(call_number, url, modio::getHeadersNoToken(), data, &modioOnOculusAuth);
  }

  void modioSteamAuth(void* object, unsigned char const* rgubTicket, u32 cubTicket, void (*callback)(void* object, ModioResponse response))
  {
    u32 call_number = modio::curlwrapper::getCallNumber();

    steam_auth_params[call_number] = new GenericRequestParams;
    steam_auth_params[call_number]->callback = callback;
    steam_auth_params[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "external/steamauth";
    url += "?api_key=" + modio::API_KEY;

    std::map<std::string, std::string> data;
    data["appdata"] = modio::curlwrapper::dataURLEncode(modio::base64Encode(rgubTicket, cubTicket));

    modio::curlwrapper::post(call_number, url, modio::getHeadersNoToken(), data, &modioOnSteamAuth);
  }

  void modioSteamAuthEncoded(void* object, char const* base64_ticket, void (*callback)(void* object, ModioResponse response))
  {
    u32 call_number = modio::curlwrapper::getCallNumber();

    steam_auth_encoded_params[call_number] = new GenericRequestParams;
    steam_auth_encoded_params[call_number]->callback = callback;
    steam_auth_encoded_params[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "external/steamauth";
    url += "?api_key=" + modio::API_KEY;

    std::map<std::string, std::string> data;
    data["appdata"] = modio::curlwrapper::dataURLEncode(std::string(base64_ticket));

    modio::curlwrapper::post(call_number, url, modio::getHeadersNoToken(), data, &modioOnSteamAuthEncoded);
  }

  void modioLinkExternalAccount(void* object, u32 service, char const* service_id, char const* email, void (*callback)(void* object, ModioResponse response))
  {
    std::map<std::string, std::string> data;
    switch (service)
    {
      case MODIO_SERVICE_STEAM:
        data["service"] = "steam";
        break;

      case MODIO_SERVICE_GALAXY:
        data["service"] = "gog";
        break;

      case MODIO_SERVICE_OCULUS:
        data["service"] = "oculus";
        break;
    }      

    data["service_id"] = service_id;
    data["email"] = modio::curlwrapper::dataURLEncode(email);

    u32 call_number = modio::curlwrapper::getCallNumber();

    link_external_account_params[call_number] = new GenericRequestParams;
    link_external_account_params[call_number]->callback = callback;
    link_external_account_params[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "external/link";

    modio::curlwrapper::post(call_number, url, modio::getHeaders(), data, &modioOnLinkExternalAccount);
  }

  void modioGetTerms(void* object, u32 service, void (*callback)(void* object, ModioResponse respons, ModioTerms terms))
  {
    std::map<std::string, std::string> data;

    switch (service)
    {
      case MODIO_SERVICE_STEAM:
        data["service"] = "steam";
        break;
      case MODIO_SERVICE_GALAXY:
        data["service"] = "gog";
        break;
      case MODIO_SERVICE_OCULUS:
        data["service"] = "oculus";
        break;
    }

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_terms_params[call_number] = new TermsParams;
    get_terms_params[call_number]->callback = callback;
    get_terms_params[call_number]->object = object;

    static const std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "authenticate/terms";
    modio::curlwrapper::post(call_number, url, modio::getHeaders(), data, &modioOnGetTerms);
  }
}