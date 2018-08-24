#include "c/methods/callbacks/ModfileCallbacks.h"

std::map< u32, GetModfileParams* > get_modfile_callbacks;
std::map< u32, GetAllModfilesParams* > get_all_modfiles_callbacks;
std::map< u32, AddModfileParams* > add_modfile_callbacks;
std::map< u32, EditModfileParams* > edit_modfile_callbacks;

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

  if(response.code == 200)
  {
    if(!get_all_modfiles_callbacks[call_number]->is_cache)
      modio::addCallToCache(get_all_modfiles_callbacks[call_number]->url, response_json);

    u32 modfiles_size = (u32)response_json["data"].size();
    ModioModfile* modfiles = new ModioModfile[modfiles_size];
    for(u32 i=0; i<modfiles_size; i++)
    {
      modioInitModfile(&modfiles[i], response_json["data"][i]);
    }
    get_all_modfiles_callbacks[call_number]->callback(get_all_modfiles_callbacks[call_number]->object, response, modfiles, modfiles_size);
    for(u32 i=0; i<modfiles_size; i++)
    {
      modioFreeModfile(&modfiles[i]);
    }
    delete[] modfiles;
  }else
  {
    get_all_modfiles_callbacks[call_number]->callback(get_all_modfiles_callbacks[call_number]->object, response, NULL, 0);
  }
  delete get_all_modfiles_callbacks[call_number];
  get_all_modfiles_callbacks.erase(call_number);
  modioFreeResponse(&response);
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
