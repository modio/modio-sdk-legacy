#include "c/schemas/ModioDownload.h"

extern "C"
{
  void modioInitDownload(ModioDownload* download, nlohmann::json download_json)
  {
    download->date_expires = 0;
    if(modio::hasKey(download_json, "date_expires"))
      download->date_expires = download_json["date_expires"];

    download->binary_url = NULL;
    if(modio::hasKey(download_json, "binary_url"))
    {
      std::string binary_url_str = download_json["binary_url"];
      download->binary_url = new char[binary_url_str.size() + 1];
      strcpy(download->binary_url, binary_url_str.c_str());
    }
  }

  void modioFreeDownload(ModioDownload* download)
  {
    if(download)
    {
      if(download->binary_url)
        delete[] download->binary_url;
    }
  }
}
