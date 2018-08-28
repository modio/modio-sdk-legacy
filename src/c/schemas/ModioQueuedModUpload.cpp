#include "c/schemas/ModioQueuedModfileUpload.h"

extern "C"
{
  void modioInitQueuedModfileUpload(ModioQueuedModfileUpload* queued_modfile_upload, nlohmann::json queued_modfile_upload_json)
  {
    queued_modfile_upload->state = 0;
    if(modio::hasKey(queued_modfile_upload_json, "state"))
      queued_modfile_upload->state = queued_modfile_upload_json["state"];

    queued_modfile_upload->mod_id = 0;
    if(modio::hasKey(queued_modfile_upload_json, "mod_id"))
      queued_modfile_upload->mod_id = queued_modfile_upload_json["mod_id"];

    queued_modfile_upload->current_progress = 0;
    if(modio::hasKey(queued_modfile_upload_json, "current_progress"))
      queued_modfile_upload->current_progress = queued_modfile_upload_json["current_progress"];

    queued_modfile_upload->total_size = 0;
    if(modio::hasKey(queued_modfile_upload_json, "total_size"))
      queued_modfile_upload->total_size = queued_modfile_upload_json["total_size"];

    queued_modfile_upload->path = NULL;
    if(modio::hasKey(queued_modfile_upload_json, "path"))
    {
      std::string path_str = queued_modfile_upload_json["path"];
      queued_modfile_upload->path = new char[path_str.size() + 1];
      strcpy(queued_modfile_upload->path, path_str.c_str());
    }

    nlohmann::json modfile_creator_json;
    if(modio::hasKey(queued_modfile_upload_json, "modfile_creator"))
      modfile_creator_json = queued_modfile_upload_json["modfile_creator"];
    modio::modioInitModfileCreatorFromJson(&(queued_modfile_upload->modio_modfile_creator), modfile_creator_json);
  }

  void modioFreeQueuedModfileUpload(ModioQueuedModfileUpload* queued_modfile_upload)
  {
    if(queued_modfile_upload)
    {
      if(queued_modfile_upload->path)
        delete[] queued_modfile_upload->path;
      modioFreeModfileCreator(&(queued_modfile_upload->modio_modfile_creator));      
    }
  }
}
