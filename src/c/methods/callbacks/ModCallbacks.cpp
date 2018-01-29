#include "c/methods/callbacks/ModCallbacks.h"

std::map< u32,GetModParams* > get_mod_callbacks;
std::map< u32,AddModParams* > add_mod_callback;
std::map< u32,DeleteModParams* > delete_mod_callbacks;
std::map< u32,GetModsParams* > get_mods_callbacks;
std::map< u32,CallbackParamReturnsId* > return_id_callbacks;
std::map< u32, GetInstallModParams* > get_install_mod_callbacks;
std::map< u32, InstallModParams* > install_mod_callbacks;

void modioOnGetMod(u32 call_number, u32 response_code, json response_json)
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

void modioOnGetMods(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  if(response.code == 200)
  {
    if(!get_mods_callbacks[call_number]->is_cache)
      modio::addCallToCache(get_mods_callbacks[call_number]->url, response_json);

    u32 mods_size = (u32)response_json["data"].size();
    ModioMod* mods = new ModioMod[mods_size];
    for(u32 i=0; i<mods_size; i++)
    {
      modioInitMod(&mods[i], response_json["data"][i]);
    }
    get_mods_callbacks[call_number]->callback(get_mods_callbacks[call_number]->object, response, mods, mods_size);
    for(u32 i=0; i<mods_size; i++)
    {
      modioFreeMod(&mods[i]);
    }
    delete[] mods;
  }else
  {
    get_mods_callbacks[call_number]->callback(get_mods_callbacks[call_number]->object, response, NULL, 0);
  }
  delete get_mods_callbacks[call_number];
  get_mods_callbacks.erase(call_number);
  modioFreeResponse(&response);
}

void modioOnModAdded(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioMod mod;
  modioInitMod(&mod, response_json);

  add_mod_callback[call_number]->callback(add_mod_callback[call_number]->object, response, mod);
  delete add_mod_callback[call_number];
  add_mod_callback.erase(call_number);
}

void modioOnModDeleted(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  delete_mod_callbacks[call_number]->callback(delete_mod_callbacks[call_number]->object, response, delete_mod_callbacks[call_number]->mod_id);
  delete delete_mod_callbacks[call_number];
  delete_mod_callbacks.erase(call_number);
}

void modioOnReturnIdCallback(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  return_id_callbacks[call_number]->callback(return_id_callbacks[call_number]->object, response, return_id_callbacks[call_number]->mod_id);
  delete return_id_callbacks[call_number];
  return_id_callbacks.erase(call_number);
}

void modioOnModDownloaded(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;
  fclose(install_mod_callbacks[call_number]->file);

  std::string destination_path_str = install_mod_callbacks[call_number]->destination_path;
  modio::createDirectory(destination_path_str);
  modio::minizipwrapper::extract(install_mod_callbacks[call_number]->zip_path, destination_path_str);
  modio::removeFile(install_mod_callbacks[call_number]->zip_path);

  if(destination_path_str[destination_path_str.size()-1] != '/')
    destination_path_str += "/";

  modio::createInstalledModJson(install_mod_callbacks[call_number]->mod_json, destination_path_str + std::string("modio.json"));

  modio::addToInstalledModsJson(install_mod_callbacks[call_number]->mod_json, destination_path_str);

  install_mod_callbacks[call_number]->callback(install_mod_callbacks[call_number]->object, response);
  delete install_mod_callbacks[call_number];
  install_mod_callbacks.erase(call_number);
  modioFreeResponse(&response);
}

void onGetInstallMod(u32 call_number, u32 response_code, json response_json)
{
  if(response_code == 200)
  {
    u32 install_call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();
    std::string file_path = modio::getModIODirectory() + "tmp/" + modio::toString((u32)response_json["modfile"]["id"]) + "_modfile.zip";
    install_mod_callbacks[install_call_number] = new InstallModParams;

    install_mod_callbacks[install_call_number]->zip_path = file_path;
    install_mod_callbacks[install_call_number]->modfile_id = response_json["modfile"]["id"];
    install_mod_callbacks[install_call_number]->mod_json = response_json;
    install_mod_callbacks[install_call_number]->mod_id = get_install_mod_callbacks[call_number]->mod_id;
    install_mod_callbacks[install_call_number]->object = get_install_mod_callbacks[call_number]->object;
    install_mod_callbacks[install_call_number]->callback = get_install_mod_callbacks[call_number]->callback;
    install_mod_callbacks[install_call_number]->destination_path = get_install_mod_callbacks[call_number]->destination_path;
    FILE* file;
    curl_off_t progress = modio::curlwrapper::getProgressIfStored(file_path);
    if(progress != 0)
    {
      file = fopen(file_path.c_str(),"ab");
    }else
    {
      file = fopen(file_path.c_str(),"wb");
    }
    install_mod_callbacks[install_call_number]->file = file;

    std::string downoad_url = response_json["modfile"]["download"]["binary_url"];

    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    modio::curlwrapper::download(install_call_number, headers, downoad_url, file_path, file, progress, &modioOnModDownloaded);
  }else
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    get_install_mod_callbacks[call_number]->callback(get_install_mod_callbacks[call_number]->object, response);
  }

  delete get_install_mod_callbacks[call_number];
  get_install_mod_callbacks.erase(call_number);
}
