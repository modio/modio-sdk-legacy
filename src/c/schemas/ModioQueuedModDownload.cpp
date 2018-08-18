#include "c/schemas/ModioQueuedModDownload.h"

extern "C"
{
  void modioInitQueuedModDownload(ModioQueuedModDownload* queued_mod_download, nlohmann::json queued_mod_download_json)
  {
    queued_mod_download->mod_id = 0;
    if(modio::hasKey(queued_mod_download_json, "mod_id"))
      queued_mod_download->mod_id = queued_mod_download_json["mod_id"];

    queued_mod_download->state = 0;
    if(modio::hasKey(queued_mod_download_json, "state"))
      queued_mod_download->state = queued_mod_download_json["state"];

    queued_mod_download->current_progress = 0;
    if(modio::hasKey(queued_mod_download_json, "current_progress"))
      queued_mod_download->current_progress = queued_mod_download_json["current_progress"];

    queued_mod_download->total_size = 0;
    if(modio::hasKey(queued_mod_download_json, "total_size"))
      queued_mod_download->total_size = queued_mod_download_json["total_size"];

    queued_mod_download->url = NULL;
    if(modio::hasKey(queued_mod_download_json, "url"))
    {
      std::string url_str = queued_mod_download_json["url"];
      queued_mod_download->url = new char[url_str.size() + 1];
      strcpy(queued_mod_download->url, url_str.c_str());
    }

    queued_mod_download->path = NULL;
    if(modio::hasKey(queued_mod_download_json, "path"))
    {
      std::string path_str = queued_mod_download_json["path"];
      queued_mod_download->path = new char[path_str.size() + 1];
      strcpy(queued_mod_download->path, path_str.c_str());
    }

    nlohmann::json mod_json;
    if(modio::hasKey(queued_mod_download_json, "mod"))
      mod_json = queued_mod_download_json["mod"];
    modioInitMod(&(queued_mod_download->mod), mod_json);
  }

  void modioFreeQueuedModDownload(ModioQueuedModDownload* queued_mod_download)
  {
    if(queued_mod_download)
    {
      if(queued_mod_download->url)
        delete[] queued_mod_download->url;
      if(queued_mod_download->path)
        delete[] queued_mod_download->path;
      modioFreeMod(&(queued_mod_download->mod));      
    }
  }
}
