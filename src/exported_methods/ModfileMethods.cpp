#include "exported_methods/ModfileMethods.h"

extern "C"
{
  struct AddModfileParams
  {
    ModioMod* mod;
    void (*callback)(ModioResponse* response, ModioModfile* modfile);
  };

  struct EditModfileParams
  {
    ModioModfile* modfile;
    void (*callback)(ModioResponse* response, ModioModfile* modfile);
  };

  map< int, AddModfileParams* > add_modfile_callbacks;
  map< int, EditModfileParams* > edit_modfile_callbacks;

  void onModfileAdded(int call_number, ModioResponse* response, json response_json)
  {
    ModioModfile* modfile = new ModioModfile;
    modioInitModfile(modfile, response_json);
    add_modfile_callbacks[call_number]->callback(response, modfile);
    add_modfile_callbacks.erase(call_number);
  }

  void onModfileEdited(int call_number, ModioResponse* response, json response_json)
  {
    edit_modfile_callbacks[call_number]->callback(response, edit_modfile_callbacks[call_number]->modfile);
    edit_modfile_callbacks.erase(call_number);
  }

  void modioAddModfile(ModioMod *mod, ModfileHandler* add_mod_file_handler, void (*callback)(ModioResponse* response, ModioModfile* modfile))
  {
    modio::minizipwrapper::compress(add_mod_file_handler->path, modio::getModIODirectory() + "tmp/modfile.zip");
    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod->id) + "/files";

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    add_modfile_callbacks[call_number] = new AddModfileParams;
    add_modfile_callbacks[call_number]->mod = mod;
    add_modfile_callbacks[call_number]->callback = callback;

    map<string, string> curlform_files;
    curlform_files["filedata"] = modio::getModIODirectory() + "tmp/modfile.zip";

    std::thread add_file_thread(modio::curlwrapper::postForm, call_number, url, headers, add_mod_file_handler->curlform_copycontents, curlform_files, &onModfileAdded);
    add_file_thread.detach();
  }

  void modioEditModfile(ModioModfile* modfile, ModfileHandler* modfile_handler, void (*callback)(ModioResponse* response, ModioModfile* modfile))
  {
    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    edit_modfile_callbacks[call_number] = new EditModfileParams;
    edit_modfile_callbacks[call_number]->modfile = modfile;
    edit_modfile_callbacks[call_number]->callback = callback;

    string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(modfile->mod) + "/files/" + modio::toString(modfile->id);

    std::thread edit_modfile_thread(modio::curlwrapper::put, call_number, url, headers, modfile_handler->curlform_copycontents, &onModfileEdited);
    edit_modfile_thread.detach();
  }
}
