#include "c++/schemas/QueuedModDownload.h"

namespace modio
{
  void QueuedModDownload::initialize(ModioQueuedModDownload queued_mod_download)
  {
    this->state = queued_mod_download.state;
    this->mod_id = queued_mod_download.mod_id;
    this->current_progress = queued_mod_download.current_progress;
    this->total_size = queued_mod_download.total_size;
    if(queued_mod_download.url)
      this->url = queued_mod_download.url;
    if(queued_mod_download.path)
      this->path = queued_mod_download.path;
    this->mod.initialize(queued_mod_download.mod);    
  }

  nlohmann::json QueuedModDownload::toJson()
  {
    nlohmann::json queued_mod_download_json;

    queued_mod_download_json["state"] = this->state;
    queued_mod_download_json["mod_id"] = this->mod_id;
    queued_mod_download_json["current_progress"] = this->current_progress;
    queued_mod_download_json["total_size"] = this->total_size;
    queued_mod_download_json["url"] = this->url;
    queued_mod_download_json["path"] = this->path;
    queued_mod_download_json["mod"] = this->mod.toJson();

    return queued_mod_download_json;
  }
}
