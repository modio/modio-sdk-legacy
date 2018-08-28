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

size_t onGetUploadData(char *ptr, size_t size, size_t nmemb, void *userdata)
{
  u32 data_size = (u32)(size * nmemb);
  return data_size;
}

size_t onGetFileData(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

size_t headerCallback(char *ptr, size_t size, size_t nitems, void *userdata)
{
  CURL *handle = (CURL *)userdata;
  char *d = (char*)ptr;

  std::string header = "";
  header.append(d, size * nitems);
  
  std::string delimiter = ": ";
  std::size_t delimiter_position = header.find(delimiter);
  std::string header_key = "";
  std::string header_value = "";
  
  if(delimiter_position != std::string::npos)
  {
    header_key.append(header.c_str(),delimiter_position);
    header_value.append(header.begin() + delimiter_position + delimiter.size(), header.end());
  }else
  {
    header_key = header_value = header;
  }

  ongoing_calls[handle]->headers[header_key] = header_value;
  
  return size * nitems;
}

}
}