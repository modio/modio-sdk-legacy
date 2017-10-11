#include "ModfileMethods.h"

namespace modio
{
  struct AddModfileParams
  {
    Mod* mod;
    function< void(int, string, Mod*) > callback;
  };

  struct EditModfileParams
  {
    Modfile* modfile;
    function< void(int, string, Modfile*) > callback;
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

  void addModfile(Mod *mod, ModfileHandler* add_mod_file_handler, function<void(int response_code, string message, Mod* mod)> callback)
  {
    minizipwrapper::compress(add_mod_file_handler->path, getModIODirectory() + "tmp/modfile.zip");
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");
    string url = MODIO_URL + MODIO_VERSION_PATH + "games/" + toString(7) + "/mods/" + toString(mod->id) + "/files";

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
  MODIO_DLL void editModfile(Modfile* modfile, ModfileHandler* modfile_handler, function<void(int response_code, string message, Modfile* modfile)> callback)
  {
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    edit_modfile_callbacks[call_number] = new EditModfileParams;
    edit_modfile_callbacks[call_number]->modfile = modfile;
    edit_modfile_callbacks[call_number]->callback = callback;

    string url = MODIO_URL + MODIO_VERSION_PATH + "games/" + toString(game_id) + "/mods/" + toString(modfile->mod) + "/files/" + toString(modfile->id);

    std::thread edit_modfile_thread(curlwrapper::put, call_number, url, headers, modfile_handler->curlform_copycontents, &onModfileEdited);
    edit_modfile_thread.detach();
  }
}
