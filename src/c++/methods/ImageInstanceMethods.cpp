#include "c++/ModIOInstance.h"

namespace modio
{
void Instance::downloadImage(const std::string &image_url, const std::string &path, const std::function<void(const modio::Response &)> &callback)
{
  const struct GenericCall *download_image_call = new GenericCall{callback};
  download_image_calls[this->current_call_id] = (GenericCall *)download_image_call;

  modioDownloadImage((void *)new u32(this->current_call_id), (char *)image_url.c_str(), (char *)path.c_str(), &onDownloadImage);

  this->current_call_id++;
}
} // namespace modio
