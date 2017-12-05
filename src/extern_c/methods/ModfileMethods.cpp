#include "extern_c/methods/ModfileMethods.h"

extern "C"
{
  struct AddModfileParams
  {
    void* object;
    void (*callback)(void* object, ModioResponse response, const ModioModfile& modfile);
  };

  struct EditModfileParams
  {
    void* object;
    int modfile_id;
    void (*callback)(void* object, ModioResponse response, const ModioModfile& modfile);
  };

  struct InstallModfileParams
  {
    void* object;
    int modfile_id;
    std::string zip_path;
    std::string destination_path;
    FILE* file;
    void (*callback)(void* object, ModioResponse response, char*);
  };

  std::map< int, AddModfileParams* > add_modfile_callbacks;
  std::map< int, EditModfileParams* > edit_modfile_callbacks;
  std::map< int, InstallModfileParams* > install_modfile_callbacks;

  void onModfileAdded(int call_number, int response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    ModioModfile modfile;
    modioInitModfile(&modfile, response_json);

    add_modfile_callbacks[call_number]->callback(add_modfile_callbacks[call_number]->object, response, modfile);
    add_modfile_callbacks.erase(call_number);
  }

  void modioAddModfile(void* object, int mod_id, ModioModfileHandler* modfile_handler, void (*callback)(void* object, ModioResponse response, const ModioModfile& modfile))
  {
    modio::minizipwrapper::compress(modfile_handler->path, modio::getModIODirectory() + "tmp/modfile.zip");
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/files";

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    add_modfile_callbacks[call_number] = new AddModfileParams;
    add_modfile_callbacks[call_number]->callback = callback;
    add_modfile_callbacks[call_number]->object = object;

    std::map<std::string, std::string> curlform_files;
    curlform_files["filedata"] = modio::getModIODirectory() + "tmp/modfile.zip";

    modio::curlwrapper::postForm(call_number, url, headers, modio::modfileHandlerToMultimap(modfile_handler), curlform_files, &onModfileAdded);
  }

  void onModfileEdited(int call_number, int response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    ModioModfile modfile;
    modioInitModfile(&modfile, response_json);

    edit_modfile_callbacks[call_number]->callback(edit_modfile_callbacks[call_number]->object, response, modfile);
    edit_modfile_callbacks.erase(call_number);
  }

  void modioEditModfile(void* object, int mod_id, int modfile_id, ModioModfileHandler* modfile_handler, void (*callback)(void* object, ModioResponse response, const ModioModfile& modfile))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    edit_modfile_callbacks[call_number] = new EditModfileParams;
    edit_modfile_callbacks[call_number]->modfile_id = modfile_id;
    edit_modfile_callbacks[call_number]->callback = callback;
    edit_modfile_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/files/" + modio::toString(modfile_id);

    std::multimap<std::string,std::string> modfile_params = modio::modfileHandlerToMultimap(modfile_handler);
    for(std::multimap<std::string,std::string>::iterator i = modfile_params.begin(); i != modfile_params.end(); i++)
    {
      if(i==modfile_params.begin())
        url+="?";
      else
        url+="&";
      url+=(*i).first + "=" + (*i).second;
    }

    modio::curlwrapper::put(call_number, url, headers, modio::modfileHandlerToMultimap(modfile_handler), &onModfileEdited);
  }

  void addToModfilesJson(int modfile_id, std::string path)
  {
    json modfiles_json;
    std::ifstream in(modio::getModIODirectory() + "modfiles.json");
    if(in.is_open())
    {
      in >> modfiles_json;
      for(json::iterator i=modfiles_json["modfiles"].begin(); i!=modfiles_json["modfiles"].end(); i++)
      {
        if((*i)["id"] == modfile_id && (*i)["path"] == path)
        {
          return;
        }
      }
    }
    in.close();

    json modfile_json;
    modfile_json["id"] = modfile_id;
    modfile_json["path"] = path;
    modfiles_json["modfiles"].push_back(modfile_json);
    std::ofstream out(modio::getModIODirectory() + "modfiles.json");
    out<<std::setw(4)<<modfiles_json<<std::endl;
    out.close();
  }

  void createModfileJson(int modfile_id, std::string file_path)
  {
    json modfile_json;
    modfile_json["modfile_id"] = modfile_id;
    std::string json_path = file_path;
    std::ofstream out(json_path);
    out<<std::setw(4)<<modfile_json<<std::endl;
    out.close();
  }

  void onModfileDownloaded(int call_number, int response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    fclose(install_modfile_callbacks[call_number]->file);
    std::string destination_path_str = install_modfile_callbacks[call_number]->destination_path;
    modio::createDirectory(destination_path_str);
    modio::minizipwrapper::extract(install_modfile_callbacks[call_number]->zip_path, destination_path_str);
    modio::removeFile(install_modfile_callbacks[call_number]->zip_path);

    if(destination_path_str[destination_path_str.size()-1] != '/')
      destination_path_str += "/";

    createModfileJson(install_modfile_callbacks[call_number]->modfile_id, destination_path_str + std::string("modio.json"));
    addToModfilesJson(install_modfile_callbacks[call_number]->modfile_id, destination_path_str);

    char* destintation_path = new char[destination_path_str.size()+1];
    strcpy(destintation_path, destination_path_str.c_str());
    install_modfile_callbacks[call_number]->callback(install_modfile_callbacks[call_number]->object, response, destintation_path);
    install_modfile_callbacks.erase(call_number);
  }

  void modioInstallModfile(void* object, u32 modfile_id, char* modfile_download, char* destination_path, void (*callback)(void* object, ModioResponse response, char* path))
  {
    std::string file_path = std::string(modio::getModIODirectory() + "tmp/") + modio::toString(modfile_id) + "_modfile.zip";

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    install_modfile_callbacks[call_number] = new InstallModfileParams;

    std::string destination_path_str = destination_path;
    destination_path_str = modio::addSlashIfNeeded(destination_path_str);
    install_modfile_callbacks[call_number]->destination_path = destination_path;
    install_modfile_callbacks[call_number]->zip_path = file_path;
    install_modfile_callbacks[call_number]->callback = callback;
    install_modfile_callbacks[call_number]->modfile_id = modfile_id;
    install_modfile_callbacks[call_number]->object = object;

    FILE* file;
    curl_off_t progress = modio::curlwrapper::getProgressIfStored(file_path);
    if(progress != 0)
    {
      file = fopen(file_path.c_str(),"ab");
    }else
    {
      file = fopen(file_path.c_str(),"wb");
    }
    install_modfile_callbacks[call_number]->file = file;

    modio::curlwrapper::download(call_number, std::string(modfile_download) + "?shhh=secret", file_path, file, progress, &onModfileDownloaded);
  }

  int modioGetModfileState(int modfile_id)
  {
    if(modioGetModfileDownloadPercentage(modfile_id))
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
        for(int i=0; i<(int)modfiles_json.size(); i++)
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

  double modioGetModfileDownloadPercentage(int modfile_id)
  {
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
    return -1;
  }
}
