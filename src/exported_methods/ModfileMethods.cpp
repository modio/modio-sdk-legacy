#include "exported_methods/ModfileMethods.h"

namespace modio
{
  struct AddModfileParams
  {
    ModioMod* mod;
    function< void(int, string, ModioMod*) > callback;
  };

  struct EditModfileParams
  {
    ModioModfile* modfile;
    function< void(int, string, ModioModfile*) > callback;
  };

  map< int, AddModfileParams* > add_modfile_callbacks;
  map< int, EditModfileParams* > edit_modfile_callbacks;

  void onModfileAdded(int call_number, int response_code, string message, json response)
  {
    add_modfile_callbacks[call_number]->callback(200, message, add_modfile_callbacks[call_number]->mod);
    add_modfile_callbacks.erase(call_number);
  }

  void onModfileEdited(int call_number, int response_code, string message, json response)
  {
    edit_modfile_callbacks[call_number]->callback(200, message, edit_modfile_callbacks[call_number]->modfile);
    edit_modfile_callbacks.erase(call_number);
  }

  void addModfile(ModioMod *mod, ModfileHandler* add_mod_file_handler, function<void(int response_code, string message, ModioMod* mod)> callback)
  {
    minizipwrapper::compress(add_mod_file_handler->path, getModIODirectory() + "tmp/modfile.zip");
    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    string url = MODIO_URL + MODIO_VERSION_PATH + "games/" + toString(modio::GAME_ID) + "/mods/" + toString(mod->id) + "/files";

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    add_modfile_callbacks[call_number] = new AddModfileParams;
    add_modfile_callbacks[call_number]->mod = mod;
    add_modfile_callbacks[call_number]->callback = callback;

    map<string, string> curlform_files;
    curlform_files["filedata"] = getModIODirectory() + "tmp/modfile.zip";

    std::thread add_file_thread(curlwrapper::postForm, call_number, url, headers, add_mod_file_handler->curlform_copycontents, curlform_files, &onModfileAdded);
    add_file_thread.detach();
  }

  //NOTE(@turupawn): Do we need the MODIO_DLL declaration here?
  MODIO_DLL void editModfile(ModioModfile* modfile, ModfileHandler* modfile_handler, function<void(int response_code, string message, ModioModfile* modfile)> callback)
  {
    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    edit_modfile_callbacks[call_number] = new EditModfileParams;
    edit_modfile_callbacks[call_number]->modfile = modfile;
    edit_modfile_callbacks[call_number]->callback = callback;

    string url = MODIO_URL + MODIO_VERSION_PATH + "games/" + toString(modio::GAME_ID) + "/mods/" + toString(modfile->mod) + "/files/" + toString(modfile->id);

    std::thread edit_modfile_thread(curlwrapper::put, call_number, url, headers, modfile_handler->curlform_copycontents, &onModfileEdited);
    edit_modfile_thread.detach();
  }
}
