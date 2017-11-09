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
    string destination_path;
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

    std::thread add_file_thread(modio::curlwrapper::postForm, call_number, url, headers, modio::modfileHandlerToMultimap(modfile_handler), curlform_files, &onModfileAdded);
    add_file_thread.detach();
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

    std::thread edit_modfile_thread(modio::curlwrapper::put, call_number, url, headers, modio::modfileHandlerToMultimap(modfile_handler), &onModfileEdited);
    edit_modfile_thread.detach();
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

  void onModfileDownloaded(int call_number, ModioResponse* response, string url, string path)
  {
    string destination_path_str = install_modfile_callbacks[call_number]->destination_path;
    modio::createDirectory(destination_path_str);
    modio::minizipwrapper::extract(path, destination_path_str);
    modio::removeFile(path);

    createModfileJson(install_modfile_callbacks[call_number]->modfile_id, install_modfile_callbacks[call_number]->destination_path + string("modio.json"));
    addToModfilesJson(install_modfile_callbacks[call_number]->modfile_id, install_modfile_callbacks[call_number]->destination_path);

    char* destintation_path = new char[destination_path_str.size()+1];
    strcpy(destintation_path, destination_path_str.c_str());
    install_modfile_callbacks[call_number]->callback(response, destintation_path);
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
    install_modfile_callbacks[call_number]->destination_path = destination_path_str;

    install_modfile_callbacks[call_number]->callback = callback;
    install_modfile_callbacks[call_number]->modfile_id = modfile->id;

    std::thread download_thread(modio::curlwrapper::download, call_number, string(modfile->download) + "?shhh=secret", file_path, &onModfileDownloaded);
    download_thread.detach();
  }
}
