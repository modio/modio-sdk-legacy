#include "c++/ModIOInstance.h"

namespace modio
{
std::map<u32, GenericCall *> download_image_calls;

void onDownloadImage(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  download_image_calls[call_id]->callback(response);

  delete (u32 *)object;
  delete download_image_calls[call_id];
  download_image_calls.erase(call_id);
}

void clearImageRequestCalls()
{
  for (auto download_image_call : download_image_calls)
    delete download_image_call.second;
  download_image_calls.clear();
}
} // namespace modio
