#include "c/methods/callbacks/ModCallbacks.h"

std::map<u32, GetModParams *> get_mod_callbacks;
std::map<u32, AddModParams *> add_mod_callbacks;
std::map<u32, GenericRequestParams *> delete_mod_callbacks;
std::map<u32, GetAllModsParams *> get_all_mods_callbacks;
std::map<u32, CallbackParamReturnsId *> return_id_callbacks;

void modioOnGetMod(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioMod mod;
  modioInitMod(&mod, response_json);

  get_mod_callbacks[call_number]->callback(get_mod_callbacks[call_number]->object, response, mod);

  delete get_mod_callbacks[call_number];
  get_mod_callbacks.erase(call_number);

  modioFreeResponse(&response);
  modioFreeMod(&mod);
}

void modioOnGetAllMods(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;
  u32 mods_size = 0;
  ModioMod *mods = NULL;

  if (response.code == 200)
  {
    if (modio::hasKey(response_json, "data"))
    {
      if (!get_all_mods_callbacks[call_number]->is_cache)
        modio::addCallToCache(get_all_mods_callbacks[call_number]->url, response_json);

      mods_size = (u32)response_json["data"].size();
      mods = new ModioMod[mods_size];
      for (u32 i = 0; i < mods_size; i++)
        modioInitMod(&mods[i], response_json["data"][i]);
    }
    else
    {
      modio::writeLogLine("Could not retreive data array from API.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  get_all_mods_callbacks[call_number]->callback(get_all_mods_callbacks[call_number]->object, response, mods, mods_size);

  delete get_all_mods_callbacks[call_number];
  get_all_mods_callbacks.erase(call_number);

  modioFreeResponse(&response);
  for (u32 i = 0; i < mods_size; i++)
    modioFreeMod(&mods[i]);
  if (mods)
    delete[] mods;
}

void modioOnModAdded(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioMod mod;
  modioInitMod(&mod, response_json);

  add_mod_callbacks[call_number]->callback(add_mod_callbacks[call_number]->object, response, mod);

  delete add_mod_callbacks[call_number];
  add_mod_callbacks.erase(call_number);

  modioFreeResponse(&response);
  modioFreeMod(&mod);
}

void modioOnModDeleted(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  delete_mod_callbacks[call_number]->callback(delete_mod_callbacks[call_number]->object, response);

  delete delete_mod_callbacks[call_number];
  delete_mod_callbacks.erase(call_number);

  modioFreeResponse(&response);
}

void modioOnReturnIdCallback(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  return_id_callbacks[call_number]->callback(return_id_callbacks[call_number]->object, response, return_id_callbacks[call_number]->mod_id);

  delete return_id_callbacks[call_number];
  return_id_callbacks.erase(call_number);

  modioFreeResponse(&response);
}

void clearModCallbackParams()
{
  for (auto get_mod_callback : get_mod_callbacks)
    delete get_mod_callback.second;
  get_mod_callbacks.clear();

  for (auto add_mod_callback : add_mod_callbacks)
    delete add_mod_callback.second;
  add_mod_callbacks.clear();

  for (auto delete_mod_callback : delete_mod_callbacks)
    delete delete_mod_callback.second;
  delete_mod_callbacks.clear();

  for (auto get_all_mods_callback : get_all_mods_callbacks)
    delete get_all_mods_callback.second;
  get_all_mods_callbacks.clear();

  for (auto return_id_callback : return_id_callbacks)
    delete return_id_callback.second;
  return_id_callbacks.clear();
}