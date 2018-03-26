#include "wrappers/CurlWriteFunctions.h"

namespace modio
{
namespace curlwrapper
{

size_t onGetJsonData(char *ptr, size_t size, size_t nmemb, void *userdata)
{
  CURL *handle = (CURL *)userdata;
  u32 data_size = (u32)(size * nmemb);
  ongoing_calls[handle]->response.append(ptr, data_size);
  return data_size;
}

size_t onGetFileData(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

}
}