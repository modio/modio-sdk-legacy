#include "c++/methods/callbacks/DownloadsInstanceCallbacks.h"

namespace modio
{
SetDownloadListenerCall *set_download_listener_call = NULL;
SetUploadListenerCall *set_upload_listener_call = NULL;
std::map<u32, GetBoolCall *> check_if_mods_are_updated_calls;

void onDownloadListener(u32 response_code, u32 mod_id)
{
  if (set_download_listener_call)
    set_download_listener_call->callback(response_code, mod_id);
}

void onUploadListener(u32 response_code, u32 mod_id)
{
  if (set_upload_listener_call)
    set_upload_listener_call->callback(response_code, mod_id);
}

void onCheckIfModsAreUpdated(void *object, ModioResponse modio_response, bool mods_are_updated)
{
  u32 call_id = (u32)((uintptr_t)object);

  modio::Response response;
  response.initialize(modio_response);

  check_if_mods_are_updated_calls[call_id]->callback(response, mods_are_updated);

  delete check_if_mods_are_updated_calls[call_id];
  check_if_mods_are_updated_calls.erase(call_id);
}
} // namespace modio
