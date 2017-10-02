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
  map< int, DownloadImageParams* > download_image_callbacks;
  map< int, DownloadImagesParams* > download_images_callbacks;
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
    get_mods_callbacks.erase(call_number);
  }

  void getMods(Filter* filter, function< void(int, vector<Mod*>) > callback)
  {
    string filter_string = getFilterString(filter);
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");
    string url = string("https://api.mod.works/v1/games/") + toString(game_id) + "/mods?" + filter_string + "&shhh=secret";

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    get_mods_callbacks[call_number] = callback;

    std::thread get_mods_thread(curlwrapper::get, call_number, url, headers, &onGetMods);
    get_mods_thread.detach();
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

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    add_mod_callback[call_number] = new AddModParams;
    add_mod_callback[call_number]->directory_path = directory_path;
    add_mod_callback[call_number]->version = version;
    add_mod_callback[call_number]->changelog = changelog;
    add_mod_callback[call_number]->callback = callback;

    string url = "https://api.mod.works/v1/games/" + toString(game_id) + "/mods";

    std::thread add_mod_thread(curlwrapper::postForm, call_number, url, headers, curlform_copycontents, curlform_files, &onModAdded);
    add_mod_thread.detach();
  }

  void onFileAdded(int call_number, int response_code, json response)
  {
    add_file_callbacks[call_number]->callback(200,add_file_callbacks[call_number]->mod);
    add_file_callbacks.erase(call_number);
  }

  void addFile(Mod *mod, string directory_path, string version, string changelog, function<void(int, Mod*)> callback)
  {
    modworks::compress(directory_path, getModworksDirectory() + "tmp/modfile.zip");
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");
    map<string, string> curlform_copycontents;
    curlform_copycontents["version"]=version;
    curlform_copycontents["changelog"]=changelog;
    map<string, string> curlform_files;
    curlform_files["filedata"] = getModworksDirectory() + "tmp/modfile.zip";
    string url = string("https://api.mod.works/v1/games/") + toString(7) + "/mods/" + toString(mod->id) + "/files";

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    add_file_callbacks[call_number] = new AddFileParams;
    add_file_callbacks[call_number]->mod = mod;
    add_file_callbacks[call_number]->callback = callback;

    std::thread add_file_thread(curlwrapper::postForm, call_number, url, headers, curlform_copycontents, curlform_files, &onFileAdded);
    add_file_thread.detach();
  }


  void onImageDownloaded(int call_number, int response_code, string url, string path)
  {
    download_image_callbacks[call_number]->callback(response_code, download_image_callbacks[call_number]->mod, path);
    download_image_callbacks.erase(call_number);
  }

  void downloadModLogoThumbnail(Mod *mod, function< void(int, Mod*, string) > callback)
  {
    string file_path = string(getModworksDirectory() + "images/") + toString(mod->id) + "_mod_logo_thumb.png";

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    download_image_callbacks[call_number] = new DownloadImageParams;
    download_image_callbacks[call_number]->mod = mod;
    download_image_callbacks[call_number]->callback = callback;

    std::thread download_image_thread(curlwrapper::download, call_number, mod->logo->thumbnail, file_path, &onImageDownloaded);

    download_image_thread.detach();
  }

  void downloadModLogoFull(Mod *mod, function< void(int, Mod*, string) > callback)
  {
    string file_path = string(getModworksDirectory() + "images/") + toString(mod->id) + "_mod_logo_full.png";

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    download_image_callbacks[call_number] = new DownloadImageParams;
    download_image_callbacks[call_number]->mod = mod;
    download_image_callbacks[call_number]->callback = callback;

    std::thread download_image_thread(curlwrapper::download, call_number, mod->logo->full, file_path, &onImageDownloaded);

    download_image_thread.detach();
  }

  void onImageFromVectorDownloaded(int call_number, int response_code, string url, string path)
  {
    download_images_callbacks[call_number]->images.push_back(path);
    if((int)download_images_callbacks[call_number]->images.size() == download_images_callbacks[call_number]->image_amount)
    {
      download_images_callbacks[call_number]->callback(response_code, download_images_callbacks[call_number]->mod, download_images_callbacks[call_number]->images);
    }
    download_images_callbacks.erase(call_number);
  }

  void downloadModMediaImagesThumbnail(Mod *mod, function< void(int, Mod*, vector<string>) > callback)
  {
    DownloadImagesParams* download_images_params = new DownloadImagesParams;
    download_images_params->mod = mod;
    download_images_params->image_amount = mod->media->images.size();
    download_images_params->callback = callback;

    for(int i=0; i<(int)mod->media->images.size();i++)
    {
      int call_number = curlwrapper::getCallCount();
      curlwrapper::advanceCallCount();
      download_images_callbacks[call_number] = download_images_params;
      createDirectory(string(getModworksDirectory() + "images/") + toString(mod->id) + "_mod_media/");
      string file_path = string(getModworksDirectory() + "images/") + toString(mod->id) + "_mod_media/" + toString(i) + "_image_thumb.png";
      std::thread download_image_thread(curlwrapper::download, call_number, mod->media->images[i]->thumbnail, file_path, &onImageFromVectorDownloaded);
      download_image_thread.detach();
    }
  }

  void downloadModMediaImagesFull(Mod *mod, function< void(int, Mod*, vector<string>) > callback)
  {
    DownloadImagesParams* download_images_params = new DownloadImagesParams;
    download_images_params->mod = mod;
    download_images_params->image_amount = mod->media->images.size();
    download_images_params->callback = callback;

    for(int i=0; i<(int)mod->media->images.size();i++)
    {
      int call_number = curlwrapper::getCallCount();
      curlwrapper::advanceCallCount();
      download_images_callbacks[call_number] = download_images_params;
      createDirectory(string(getModworksDirectory() + "images/") + toString(mod->id) + "_mod_media/");
      string file_path = string(getModworksDirectory() + "images/") + toString(mod->id) + "_mod_media/" + toString(i) + "_image_full.png";
      std::thread download_image_thread(curlwrapper::download, call_number, mod->media->images[i]->full, file_path, &onImageFromVectorDownloaded);
      download_image_thread.detach();
    }
  }

  void onModfileDownloaded(int call_number, int response_code, string url, string path)
  {
    string destintation_path = download_modfile_callbacks[call_number]->destination_path;
    createDirectory(destintation_path);
    extract(path, destintation_path);
    removeFile(path);
    download_modfile_callbacks[call_number]->callback(response_code, download_modfile_callbacks[call_number]->mod, path);
    download_modfile_callbacks.erase(call_number);
  }

  void installMod(Mod *mod, string destination_path, function< void(int, Mod*, string) > callback)
  {
    string file_path = string(getModworksDirectory() + "tmp/") + toString(mod->modfile->id) + "_modfile.zip";

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    download_modfile_callbacks[call_number] = new DownloadModfileParams;
    download_modfile_callbacks[call_number]->mod = mod;
    download_modfile_callbacks[call_number]->destination_path = destination_path;
    download_modfile_callbacks[call_number]->callback = callback;

    std::thread download_thread(curlwrapper::download, call_number, mod->modfile->download + "?shhh=secret", file_path, &onModfileDownloaded);
    download_thread.detach();
  }
}
