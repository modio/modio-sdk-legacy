#include "c/methods/ModfileMethods.h"

extern "C"
{
  void modioAddModfile(void* object, u32 mod_id, ModioModfileCreator modfile_creator, void (*callback)(void* object, ModioResponse response, ModioModfile modfile))
  {
    modio::minizipwrapper::compress(modfile_creator.path, modio::getModIODirectory() + "tmp/modfile.zip");
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/files";

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    add_modfile_callbacks[call_number] = new AddModfileParams;
    add_modfile_callbacks[call_number]->callback = callback;
    add_modfile_callbacks[call_number]->object = object;

    std::map<std::string, std::string> curlform_files;
    curlform_files["filedata"] = modio::getModIODirectory() + "tmp/modfile.zip";

    modio::curlwrapper::postForm(call_number, url, headers, modio::convertModfileCreatorToMultimap(&modfile_creator), curlform_files, &modioOnModfileAdded);
  }

  void modioEditModfile(void* object, u32 mod_id, u32 modfile_id, ModioModfileEditor modfile_editor, void (*callback)(void* object, ModioResponse response, ModioModfile modfile))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    edit_modfile_callbacks[call_number] = new EditModfileParams;
    edit_modfile_callbacks[call_number]->modfile_id = modfile_id;
    edit_modfile_callbacks[call_number]->callback = callback;
    edit_modfile_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/files/" + modio::toString(modfile_id);

    std::multimap<std::string,std::string> modfile_params = modio::convertModfileEditorToMultimap(&modfile_editor);
    for(std::multimap<std::string,std::string>::iterator i = modfile_params.begin(); i != modfile_params.end(); i++)
    {
      if(i==modfile_params.begin())
        url+="?";
      else
        url+="&";
      url+=(*i).first + "=" + (*i).second;
    }

    modio::curlwrapper::put(call_number, url, headers, modio::convertModfileEditorToMultimap(&modfile_editor), &modioOnModfileEdited);
  }

  u32 modioGetModfileState(u32 modfile_id)
  {
    if(modioGetModfileDownloadPercentage(modfile_id) != -1)
    {
      return MODIO_MODFILE_INSTALLING;
    }
    std::ifstream installed_mods_file(modio::getModIODirectory() + "installed_mods.json");
    if(installed_mods_file.is_open())
    {
      json installed_mods_json;
      try
      {
        installed_mods_file >> installed_mods_json;
        for(u32 i=0; i<installed_mods_json["mods"].size(); i++)
        {
          if(modfile_id == installed_mods_json["mods"][i]["id"])
          {
            return MODIO_MODFILE_INSTALLED;
          }
        }
      }catch(json::parse_error &e)
      {
        modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
      }
    }
    return MODIO_MODFILE_NOT_INSTALLED;
  }

  bool modioUninstallModfile(u32 modfile_id)
  {
    modio::updateInstalledModsJson();
    std::string modfile_path = modio::getInstalledModPath(modfile_id);

    bool result = modfile_path != "" && modio::checkIfModIsStillInstalled(modfile_path, modfile_id) && modio::removeDirectory(modfile_path);
    modio::updateInstalledModsJson();
    return result;
  }

  u32 modioGetInstalledModfilesCount()
  {
    std::ifstream installed_mods_file(modio::getModIODirectory() + "installed_mods.json");
    if(installed_mods_file.is_open())
    {
      json installed_mods_json;
      try
      {
        installed_mods_file >> installed_mods_json;
        installed_mods_json = installed_mods_json["mods"];
        return (u32)installed_mods_json.size();
      }catch(json::parse_error &e)
      {
        modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
      }
    }
    return 0;
  }

  u32 modioGetInstalledModfileId(u32 index)
  {
    std::ifstream installed_mods_file(modio::getModIODirectory() + "installed_mods.json");
    if(installed_mods_file.is_open())
    {
      json installed_mods_json;
      try
      {
        installed_mods_file >> installed_mods_json;
        if(index >= installed_mods_json["mods"].size())
        {
          return 0;
        }
        return installed_mods_json["mods"][index]["modfile_id"];
      }catch(json::parse_error &e)
      {
        modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
      }
    }
    return 0;
  }
}
