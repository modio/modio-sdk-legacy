#include "c++/schemas/QueuedModDownload.h"
#include "c/ModioC.h"                      // for ModioQueuedModDownload
#include "dependencies/nlohmann/json.hpp"  // for json

namespace modio
{
void QueuedModDownload::initialize(ModioQueuedModDownload queued_mod_download)
{
  state = queued_mod_download.state;
  mod_id = queued_mod_download.mod_id;
  current_progress = queued_mod_download.current_progress;
  total_size = queued_mod_download.total_size;
  if (queued_mod_download.url)
    url = queued_mod_download.url;
  if (queued_mod_download.path)
    path = queued_mod_download.path;
  mod.initialize(queued_mod_download.mod);
}

nlohmann::json toJson(QueuedModDownload &queued_mod_download)
{
  nlohmann::json queued_mod_download_json;

  queued_mod_download_json["state"] = queued_mod_download.state;
  queued_mod_download_json["mod_id"] = queued_mod_download.mod_id;
  queued_mod_download_json["current_progress"] = queued_mod_download.current_progress;
  queued_mod_download_json["total_size"] = queued_mod_download.total_size;
  queued_mod_download_json["url"] = queued_mod_download.url;
  queued_mod_download_json["path"] = queued_mod_download.path;
  queued_mod_download_json["mod"] = modio::toJson(queued_mod_download.mod);

  return queued_mod_download_json;
}
} // namespace modio
