#include "ModfileMethods.h"

namespace modio
{
  struct AddModfileParams
  {
    Mod* mod;
    function< void(int, string, Mod*) > callback;
  };

  map< int, AddModfileParams* > add_modfile_callbacks;

  void onFileAdded(int call_number, int response_code, string message, json response)
  {
    add_modfile_callbacks[call_number]->callback(200, message, add_modfile_callbacks[call_number]->mod);
    add_modfile_callbacks.erase(call_number);
  }

  void addModfile(Mod *mod, ModfileHandler* add_mod_file_handler, function<void(int response_code, string message, Mod* mod)> callback)
  {
    minizipwrapper::compress(add_mod_file_handler->path, getModIODirectory() + "tmp/modfile.zip");
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");
    string url = string("https://api.mod.works/v1/games/") + toString(7) + "/mods/" + toString(mod->id) + "/files";

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    add_modfile_callbacks[call_number] = new AddModfileParams;
    add_modfile_callbacks[call_number]->mod = mod;
    add_modfile_callbacks[call_number]->callback = callback;

    map<string, string> curlform_files;
    curlform_files["filedata"] = getModIODirectory() + "tmp/modfile.zip";

    std::thread add_file_thread(curlwrapper::postForm, call_number, url, headers, add_mod_file_handler->curlform_copycontents, curlform_files, &onFileAdded);
    add_file_thread.detach();
  }
}
