#include "c/methods/ExternalAuthenticationMethods.h"

extern "C"
{
  void modioGalaxyAuth(void* object, char const* appdata, void (*callback)(void* object, ModioResponse response))
  {
    u32 call_number = modio::curlwrapper::getCallNumber();

    galaxy_auth_params[call_number] = new GenericRequestParams;
    galaxy_auth_params[call_number]->callback = callback;
    galaxy_auth_params[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "external/galaxyauth";
    url += "?appdata=" + std::string(appdata);

    modio::curlwrapper::post(call_number, url, std::vector<std::string>(), std::map<std::string, std::string>(), &modioOnGalaxyAuth);
  }

  void modioSteamAuth(void* object, unsigned char const* rgubTicket, u32 cubTicket, void (*callback)(void* object, ModioResponse response))
  {
    u32 call_number = modio::curlwrapper::getCallNumber();

    steam_auth_params[call_number] = new GenericRequestParams;
    steam_auth_params[call_number]->callback = callback;
    steam_auth_params[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "external/steamauth";
    url += "?appdata=" + modio::base64Encode(rgubTicket, cubTicket);

    modio::curlwrapper::post(call_number, url, std::vector<std::string>(), std::map<std::string, std::string>(), &modioOnSteamAuth);
  }

  void modioSteamAuthEncoded(void* object, char const* base64_ticket, void (*callback)(void* object, ModioResponse response))
  {
    u32 call_number = modio::curlwrapper::getCallNumber();

    steam_auth_encoded_params[call_number] = new GenericRequestParams;
    steam_auth_encoded_params[call_number]->callback = callback;
    steam_auth_encoded_params[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "external/steamauth";
    url += "?appdata=" + std::string(base64_ticket);

    modio::curlwrapper::post(call_number, url, std::vector<std::string>(), std::map<std::string, std::string>(), &modioOnSteamAuth);
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
    }      

    data["service_id"] = service_id;
    data["email"] = email;

    u32 call_number = modio::curlwrapper::getCallNumber();

    link_external_account_params[call_number] = new GenericRequestParams;
    link_external_account_params[call_number]->callback = callback;
    link_external_account_params[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "external/link";

    modio::curlwrapper::post(call_number, url, std::vector<std::string>(), data, &modioOnLinkExternalAccount);
  }
}
