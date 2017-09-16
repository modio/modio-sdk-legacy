#include "ModMethods.h"

namespace modworks
{
  struct AddModParams
  {
    string directory_path;
    string version;
    string changelog;
    function<void(int, Mod*)> callback;
  };

  map< int,AddModParams* > add_mod_callback;
  map< int,function<void(int, vector<Mod*>)> > get_mods_callbacks;

  map< int, AddFileParams* > add_file_callbacks;
  map< int, DownloadThumbnailParams* > download_thumbnail_callbacks;
  map< int, DownloadModfileParams* > download_modfile_callbacks;

  void onGetMods(int call_number, int response_code, json response)
  {
    vector<Mod*> mods;

    if(response_code == 200)
    {
      for(int i=0;i<(int)response["data"].size();i++)
      {
        Mod* mod = new Mod(response["data"][i]);
        mods.push_back(mod);
      }
    }

    get_mods_callbacks[call_number](response_code,mods);
  }

  void getMods(function< void(int, vector<Mod*>) > callback)
  {
    writeLogLine("getMods call", verbose);
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");
    string url = string("https://api.mod.works/v1/games/") + toString(game_id) + "/mods" + "?shhh=secret";

    int call_number = getCallCount();
    advanceCallCount();

    get_mods_callbacks[call_number] = callback;

    std::thread get_mods_thread(get, call_number, url, headers, &onGetMods);
    get_mods_thread.detach();
    writeLogLine("getJson thread detached", verbose);
  }

  void onModAdded(int call_number, int response_code, json response)
  {
    Mod* mod = new Mod(response);
    addFile(mod, add_mod_callback[call_number]->directory_path,
                  add_mod_callback[call_number]->version,
                  add_mod_callback[call_number]->changelog,
                  add_mod_callback[call_number]->callback);
    add_mod_callback.erase(call_number);
  }

  void addMod(string name, string homepage, string summary, string logo_path,
                    string directory_path, string version, string changelog,
                    function<void(int, Mod*)> callback)
  {
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");
    map<string, string> curlform_copycontents;
    curlform_copycontents["name"]=name;
    curlform_copycontents["homepage"]=homepage;
    curlform_copycontents["summary"]=summary;
    map<string, string> curlform_files;
    curlform_files["logo"]=logo_path;

    map<string,string> params;
    params["directory_path"] = directory_path;
    params["version"] = version;
    params["changelog"] = changelog;

    int call_number = getCallCount();
    advanceCallCount();

    add_mod_callback[call_number] = new AddModParams;
    add_mod_callback[call_number]->directory_path = directory_path;
    add_mod_callback[call_number]->version = version;
    add_mod_callback[call_number]->changelog = changelog;
    add_mod_callback[call_number]->callback = callback;

    string url = "https://api.mod.works/v1/games/" + toString(game_id) + "/mods";

    std::thread add_mod_thread(modworks::postForm, call_number, url, headers, curlform_copycontents, curlform_files, &onModAdded);
    add_mod_thread.detach();
  }

  void onFileAdded(int call_number, int response_code, json response)
  {
    add_file_callbacks[call_number]->callback(200,add_file_callbacks[call_number]->mod);
    add_file_callbacks.erase(call_number);
  }

  void addFile(Mod *mod, string directory_path, string version, string changelog, function<void(int, Mod*)> callback)
  {
    modworks::compress(directory_path,".modworks/tmp/modfile.zip");
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");
    map<string, string> curlform_copycontents;
    curlform_copycontents["version"]=version;
    curlform_copycontents["changelog"]=changelog;
    map<string, string> curlform_files;
    curlform_files["filedata"]=".modworks/tmp/modfile.zip";
    string url = string("https://api.mod.works/v1/games/") + toString(7) + "/mods/" + toString(mod->id) + "/files";

    int call_number = getCallCount();
    advanceCallCount();

    add_file_callbacks[call_number] = new AddFileParams;
    add_file_callbacks[call_number]->mod = mod;
    add_file_callbacks[call_number]->callback = callback;

    std::thread add_file_thread(modworks::postForm, call_number, url, headers, curlform_copycontents, curlform_files, &onFileAdded);
    add_file_thread.detach();
  }


  void onThumbnailDownloaded(int call_number, int response_code, string url, string path)
  {
    download_thumbnail_callbacks[call_number]->callback(response_code, download_thumbnail_callbacks[call_number]->mod, path);
  }

  void downloadLogoThumbnail(Mod *mod, function< void(int, Mod*, string) > callback)
  {
    writeLogLine("Mod::downloadLogoThumbnail call", verbose);
    string file_path = string(".modworks/images/") + toString(mod->game) + "_" + toString(mod->id) + "_thumb.png";

    int call_number = getCallCount();
    advanceCallCount();

    download_thumbnail_callbacks[call_number] = new DownloadThumbnailParams;
    download_thumbnail_callbacks[call_number]->mod = mod;
    download_thumbnail_callbacks[call_number]->callback = callback;

    //std::thread download_thumbnail_thread(download, call_number, mod->logo_thumbnail_url, file_path, &onThumbnailDownloaded);
    std::thread download_thumbnail_thread(static_cast<void(*)(int call_number, string url, string path, function< void(int, int, string, string) > callback)>(&download), call_number, mod->logo_thumbnail_url, file_path, &onThumbnailDownloaded);

    download_thumbnail_thread.detach();
    writeLogLine("downloadModFile detached", verbose);
  }

  void onModfileDownloaded(int call_number, int response_code, string url, string path)
  {
    string destintation_path = download_modfile_callbacks[call_number]->destination_path;
    createDirectory(destintation_path);
    extract(path, destintation_path);
    download_modfile_callbacks[call_number]->callback(response_code, download_modfile_callbacks[call_number]->mod, path);
  }

  void download(Mod *mod, string destination_path, function< void(int, Mod*, string) > callback)
  {
    writeLogLine("Mod::download call", verbose);
    string file_path = string(".modworks/tmp/") + toString(mod->game) + "_" + toString(mod->id) + "_modfile.zip";

    int call_number = getCallCount();
    advanceCallCount();

    download_modfile_callbacks[call_number] = new DownloadModfileParams;
    download_modfile_callbacks[call_number]->mod = mod;
    download_modfile_callbacks[call_number]->destination_path = destination_path;
    download_modfile_callbacks[call_number]->callback = callback;

    std::thread download_thread(static_cast<void(*)(int call_number, string url, string path, function< void(int, int, string, string) > callback)>(&download), call_number, mod->download_url + "?shhh=secret", file_path, &onModfileDownloaded);
    download_thread.detach();

    writeLogLine("downloadRedirect detached", verbose);
  }
}
