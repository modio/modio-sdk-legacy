#include "exported_methods/ModfileMethods.h"

extern "C"
{
  struct AddModfileParams
  {
    void (*callback)(ModioResponse* response, ModioModfile* modfile);
  };

  struct EditModfileParams
  {
    int modfile_id;
    void (*callback)(ModioResponse* response, int modfile_id);
  };

  struct InstallModfileParams
  {
    int modfile_id;
    string zip_path;
    string destination_path;
    FILE* file;
    void (*callback)(ModioResponse* response, char*);
  };

  map< int, AddModfileParams* > add_modfile_callbacks;
  map< int, EditModfileParams* > edit_modfile_callbacks;
  map< int, InstallModfileParams* > install_modfile_callbacks;

  void onModfileAdded(int call_number, ModioResponse* response, json response_json)
  {
    ModioModfile* modfile = new ModioModfile;
    modioInitModfile(modfile, response_json);
    add_modfile_callbacks[call_number]->callback(response, modfile);
    add_modfile_callbacks.erase(call_number);
  }

  void onModfileEdited(int call_number, ModioResponse* response, json response_json)
  {
    edit_modfile_callbacks[call_number]->callback(response, edit_modfile_callbacks[call_number]->modfile_id);
    edit_modfile_callbacks.erase(call_number);
  }

  void modioAddModfile(int mod_id, ModioModfileHandler* modfile_handler, void (*callback)(ModioResponse* response, ModioModfile* modfile))
  {
    modio::minizipwrapper::compress(modfile_handler->path, modio::getModIODirectory() + "tmp/modfile.zip");
    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/files";

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    add_modfile_callbacks[call_number] = new AddModfileParams;
    add_modfile_callbacks[call_number]->callback = callback;

    map<string, string> curlform_files;
    curlform_files["filedata"] = modio::getModIODirectory() + "tmp/modfile.zip";

    modio::curlwrapper::postForm(call_number, url, headers, modio::modfileHandlerToMultimap(modfile_handler), curlform_files, &onModfileAdded);
  }

  void modioEditModfile(int mod_id, int modfile_id, ModioModfileHandler* modfile_handler, void (*callback)(ModioResponse* response, int modfile_id))
  {
    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    edit_modfile_callbacks[call_number] = new EditModfileParams;
    edit_modfile_callbacks[call_number]->modfile_id = modfile_id;
    edit_modfile_callbacks[call_number]->callback = callback;

    string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/files/" + modio::toString(modfile_id);

    modio::curlwrapper::put(call_number, url, headers, modio::modfileHandlerToMultimap(modfile_handler), &onModfileEdited);
  }

  void addToModfilesJson(int modfile_id, string path)
  {
    json modfiles_json;
    ifstream in(modio::getModIODirectory() + "modfiles.json");
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
    ofstream out(modio::getModIODirectory() + "modfiles.json");
    out<<setw(4)<<modfiles_json<<endl;
    out.close();
  }

  void createModfileJson(int modfile_id, string file_path)
  {
    json modfile_json;
    modfile_json["modfile_id"] = modfile_id;
    string json_path = file_path;
    std::ofstream out(json_path);
    out<<setw(4)<<modfile_json<<endl;
    out.close();
  }

  void onModfileDownloaded(int call_number, ModioResponse* modio_response, json response)
  {
    fclose(install_modfile_callbacks[call_number]->file);
    string destination_path_str = install_modfile_callbacks[call_number]->destination_path;
    modio::createDirectory(destination_path_str);
    modio::minizipwrapper::extract(install_modfile_callbacks[call_number]->zip_path, destination_path_str);
    modio::removeFile(install_modfile_callbacks[call_number]->zip_path);

    if(destination_path_str[destination_path_str.size()-1] != '/')
      destination_path_str += "/";

    createModfileJson(install_modfile_callbacks[call_number]->modfile_id, destination_path_str + string("modio.json"));
    addToModfilesJson(install_modfile_callbacks[call_number]->modfile_id, destination_path_str);

    char* destintation_path = new char[destination_path_str.size()+1];
    strcpy(destintation_path, destination_path_str.c_str());
    install_modfile_callbacks[call_number]->callback(modio_response, destintation_path);
    install_modfile_callbacks.erase(call_number);
  }

  void modioInstallModfile(ModioModfile *modfile, char* destination_path, void (*callback)(ModioResponse* response, char* path))
  {
    string file_path = string(modio::getModIODirectory() + "tmp/") + modio::toString(modfile->id) + "_modfile.zip";

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    install_modfile_callbacks[call_number] = new InstallModfileParams;

    string destination_path_str = destination_path;
    destination_path_str = modio::addSlashIfNeeded(destination_path_str);
    install_modfile_callbacks[call_number]->destination_path = destination_path;
    install_modfile_callbacks[call_number]->zip_path = file_path;
    install_modfile_callbacks[call_number]->callback = callback;
    install_modfile_callbacks[call_number]->modfile_id = modfile->id;

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

    modio::curlwrapper::download(call_number, string(modfile->download) + "?shhh=secret", file_path, file, progress, &onModfileDownloaded);
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
        modio::writeLogLine(string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
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
