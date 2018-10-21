#include "c/methods/callbacks/ModfileCallbacks.h"

std::map<u32, GetModfileParams *> get_modfile_callbacks;
std::map<u32, GetAllModfilesParams *> get_all_modfiles_callbacks;
std::map<u32, AddModfileParams *> add_modfile_callbacks;
std::map<u32, EditModfileParams *> edit_modfile_callbacks;
std::map<u32, DeleteModfileParams *> delete_modfile_callbacks;

void modioOnGetModfile(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioModfile modfile;
  modioInitModfile(&modfile, response_json);

  get_modfile_callbacks[call_number]->callback(get_modfile_callbacks[call_number]->object, response, modfile);

  delete get_modfile_callbacks[call_number];
  get_modfile_callbacks.erase(call_number);

  modioFreeResponse(&response);
  modioFreeModfile(&modfile);
}

void modioOnGetAllModfiles(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;
  u32 modfiles_size = 0;
  ModioModfile *modfiles = NULL;

  if (response.code == 200)
  {
    if (modio::hasKey(response_json, "data"))
    {
      if (!get_all_modfiles_callbacks[call_number]->is_cache)
        modio::addCallToCache(get_all_modfiles_callbacks[call_number]->url, response_json);

      modfiles_size = (u32)response_json["data"].size();
      modfiles = new ModioModfile[modfiles_size];

      for (u32 i = 0; i < modfiles_size; i++)
        modioInitModfile(&modfiles[i], response_json["data"][i]);
    }
    else
    {
      modio::writeLogLine("Could not retreive data array from API.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  get_all_modfiles_callbacks[call_number]->callback(get_all_modfiles_callbacks[call_number]->object, response, modfiles, modfiles_size);

  delete get_all_modfiles_callbacks[call_number];
  get_all_modfiles_callbacks.erase(call_number);

  modioFreeResponse(&response);
  for (u32 i = 0; i < modfiles_size; i++)
    modioFreeModfile(&modfiles[i]);
  if (modfiles)
    delete[] modfiles;
}

void modioOnModfileAdded(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioModfile modfile;
  modioInitModfile(&modfile, response_json);

  add_modfile_callbacks[call_number]->callback(add_modfile_callbacks[call_number]->object, response, modfile);

  delete add_modfile_callbacks[call_number];
  add_modfile_callbacks.erase(call_number);

  modioFreeResponse(&response);
  modioFreeModfile(&modfile);
}

void modioOnModfileEdited(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioModfile modfile;
  modioInitModfile(&modfile, response_json);

  edit_modfile_callbacks[call_number]->callback(edit_modfile_callbacks[call_number]->object, response, modfile);

  delete edit_modfile_callbacks[call_number];
  edit_modfile_callbacks.erase(call_number);

  modioFreeResponse(&response);
  modioFreeModfile(&modfile);
}

void modioOnModfileDeleted(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  delete_modfile_callbacks[call_number]->callback(delete_modfile_callbacks[call_number]->object, response);

  delete delete_modfile_callbacks[call_number];
  delete_modfile_callbacks.erase(call_number);

  modioFreeResponse(&response);
}

void clearModfileCallbackParams()
{
  for (auto get_modfile_callback : get_modfile_callbacks)
    delete get_modfile_callback.second;
  get_modfile_callbacks.clear();

  for (auto get_all_modfiles_callback : get_all_modfiles_callbacks)
    delete get_all_modfiles_callback.second;
  get_all_modfiles_callbacks.clear();

  for (auto add_modfile_callback : add_modfile_callbacks)
    delete add_modfile_callback.second;
  add_modfile_callbacks.clear();

  for (auto edit_modfile_callback : edit_modfile_callbacks)
    delete edit_modfile_callback.second;
  edit_modfile_callbacks.clear();

  for (auto delete_modfile_callback : delete_modfile_callbacks)
    delete delete_modfile_callback.second;
  delete_modfile_callbacks.clear();
}