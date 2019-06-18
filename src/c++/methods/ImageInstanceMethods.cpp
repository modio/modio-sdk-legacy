#include "c++/ModIOInstance.h"

namespace modio
{
void Instance::downloadImage(const std::string &image_url, const std::string &path, const std::function<void(const modio::Response &)> &callback)
{
  struct GenericCall *download_image_call = new GenericCall{callback};
  download_image_calls[current_call_id] = download_image_call;

  modioDownloadImage((void*)((uintptr_t)current_call_id), image_url.c_str(), path.c_str(), &onDownloadImage);

  current_call_id++;
}
} // namespace modio
