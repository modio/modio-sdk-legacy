#include "c/methods/callbacks/DownloadsCallbacks.h"

std::map< u32, GetInstallModParams* > get_install_mod_callbacks;

void onGetInstallMod(u32 call_number, u32 response_code, json response_json)
{
  if(response_code == 200)
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    ModioMod modio_mod;
    modioInitMod(&modio_mod, response_json);
    ModioMod* modio_modx = &modio_mod;    
    modio::curlwrapper::queueModDownload(modio_modx);
  }else
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;
    //download listener callback
  }
}
