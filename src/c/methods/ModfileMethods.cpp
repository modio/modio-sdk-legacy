#include "c/methods/ModfileMethods.h"

extern "C"
{
  struct AddModfileParams
  {
    void* object;
    void (*callback)(void* object, ModioResponse response, ModioModfile modfile);
  };

  struct EditModfileParams
  {
    void* object;
    u32 modfile_id;
    void (*callback)(void* object, ModioResponse response, ModioModfile modfile);
  };

  std::map< u32, AddModfileParams* > add_modfile_callbacks;
  std::map< u32, EditModfileParams* > edit_modfile_callbacks;

  void modioOnModfileAdded(u32 call_number, u32 response_code, json response_json)
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

  void modioOnModfileEdited(u32 call_number, u32 response_code, json response_json)
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
    std::ifstream modfiles_file(modio::getModIODirectory() + "modfiles.json");
    if(modfiles_file.is_open())
    {
      json modfiles_json;
      try
      {
        modfiles_file >> modfiles_json;
        modfiles_json = modfiles_json["modfiles"];
        for(u32 i=0; i<modfiles_json.size(); i++)
        {
          if(modfile_id == modfiles_json[i]["id"])
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

  double modioGetModfileDownloadPercentage(u32 modfile_id)
  {
    /*
    if(install_modfile_callbacks.find(modio::curlwrapper::getOngoingCall()) != install_modfile_callbacks.end())
    {
      InstallModfileParams* install_modfile_params = install_modfile_callbacks[modio::curlwrapper::getOngoingCall()];

      if(install_modfile_params->modfile_id == modfile_id)
      {
        modio::CurrentDownloadInfo current_download_info = modio::curlwrapper::getCurrentDownloadInfo();
        if(current_download_info.download_progress == 0)
          return 0;
        double result = current_download_info.download_progress;
        result /= current_download_info.download_total;
        return result * 100;
      }
    }
    */
    return -1;
  }

  bool modioUninstallModfile(u32 modfile_id)
  {
    modio::updateModfilesJson();
    std::string modfile_path = modio::getModfilePath(modfile_id);
    bool result = modfile_path != "" && modio::checkIfModIsStillInstalled(modfile_path, modfile_id) && modio::removeDirectory(modfile_path);
    modio::updateModfilesJson();
    return result;
  }

  u32 modioGetInstalledModfilesCount()
  {
    std::ifstream modfiles_file(modio::getModIODirectory() + "modfiles.json");
    if(modfiles_file.is_open())
    {
      json modfiles_json;
      try
      {
        modfiles_file >> modfiles_json;
        modfiles_json = modfiles_json["modfiles"];
        return (u32)modfiles_json.size();
      }catch(json::parse_error &e)
      {
        modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
      }
    }
    return 0;
  }

  u32 modioGetInstalledModfileId(u32 index)
  {
    std::ifstream modfiles_file(modio::getModIODirectory() + "modfiles.json");
    if(modfiles_file.is_open())
    {
      json modfiles_json;
      try
      {
        modfiles_file >> modfiles_json;
        modfiles_json = modfiles_json["modfiles"];
        if(index >= modfiles_json.size())
        {
          return 0;
        }
        return modfiles_json[index]["id"];
      }catch(json::parse_error &e)
      {
        modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
      }
    }
    return 0;
  }
}
