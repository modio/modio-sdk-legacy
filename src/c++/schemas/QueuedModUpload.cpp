#include "c++/schemas/QueuedModfileUpload.h"

namespace modio
{
void QueuedModfileUpload::initialize(ModioQueuedModfileUpload queued_modfile_upload)
{
  this->state = queued_modfile_upload.state;
  this->mod_id = queued_modfile_upload.mod_id;
  this->current_progress = queued_modfile_upload.current_progress;
  this->total_size = queued_modfile_upload.total_size;
  if (queued_modfile_upload.path)
    this->path = queued_modfile_upload.path;
  //TODO: Should this exists?
  //this->modfile_creator.initialize(queued_modfile_upload.modio_modfile_creator);
}

nlohmann::json toJson(QueuedModfileUpload &queued_modfile_upload)
{
  nlohmann::json queued_modfile_upload_json;

  queued_modfile_upload_json["state"] = queued_modfile_upload.state;
  queued_modfile_upload_json["current_progress"] = queued_modfile_upload.current_progress;
  queued_modfile_upload_json["total_size"] = queued_modfile_upload.total_size;
  queued_modfile_upload_json["path"] = queued_modfile_upload.path;

  queued_modfile_upload_json["modfile_creator"] = modio::toJson(queued_modfile_upload.modfile_creator);

  return queued_modfile_upload_json;
}
} // namespace modio
