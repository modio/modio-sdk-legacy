#include "c++/ModIOInstance.h"

namespace modio
{
  std::map<u32, DownloadImageCall*> download_image_calls;
  std::map<u32, EditModLogoCall*> edit_mod_logo_calls;

  void onDownloadImage(void* object, ModioResponse modio_response)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    download_image_calls[call_id]->callback(response);

    delete (u32*)object;
    delete download_image_calls[call_id];
    download_image_calls.erase(call_id);
  }

  void onEditModLogo(void* object, ModioResponse modio_response, u32 mod_id)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    edit_mod_logo_calls[call_id]->callback(response, mod_id);

    delete (u32*)object;
    delete edit_mod_logo_calls[call_id];
    edit_mod_logo_calls.erase(call_id);
  }
}
