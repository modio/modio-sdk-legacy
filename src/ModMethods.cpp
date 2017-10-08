#include "ModMethods.h"

namespace modio
{
  struct AddModParams
  {
    string directory_path;
    string version;
    string changelog;
    function<void(int, string, Mod*)> callback;
  };

  struct AddFileParams
  {
    Mod* mod;
    function< void(int, string, Mod*) > callback;
  };

  struct DownloadImageParams
  {
    Mod* mod;
    function< void(int, string, Mod*, string) > callback;
  };

  struct DownloadImagesParams
  {
    Mod* mod;
    int image_amount;
    vector<string> images;
    function< void(int, string, Mod*, vector<string>) > callback;
  };

  struct DeleteModParams
  {
    Mod* mod;
    function<void(int, string, Mod*)> callback;
  };

  struct DownloadModfileParams
  {
    Mod* mod;
    string destination_path;
    function< void(int, string, Mod*, string) > callback;
  };

  map< int,AddModParams* > add_mod_callback;
  map< int,DeleteModParams* > delete_mod_callbacks;
  map< int,function<void(int, string, vector<Mod*>)> > get_mods_callbacks;

  map< int, AddFileParams* > add_file_callbacks;
  map< int, DownloadImageParams* > download_image_callbacks;
  map< int, DownloadImagesParams* > download_images_callbacks;
  map< int, DownloadModfileParams* > download_modfile_callbacks;

  void onGetMods(int call_number, int response_code, string message, json response)
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

    get_mods_callbacks[call_number](response_code, message, mods);
    get_mods_callbacks.erase(call_number);
  }

  void getMods(Filter* filter, function< void(int response_code, string message, vector<Mod*> mods) > callback)
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

  void onModAdded(int call_number, int response_code, string message, json response)
  {
    Mod* mod = new Mod(response);
    add_mod_callback[call_number]->callback(response_code, message, mod);
    add_mod_callback.erase(call_number);
  }

  void editMod(Mod* mod, ModHandler* add_mod_handler, function<void(int response_code, string message, Mod* mod)> callback)
  {
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    add_mod_callback[call_number] = new AddModParams;
    add_mod_callback[call_number]->callback = callback;

    string url = "https://api.mod.works/v1/games/" + toString(game_id) + "/mods/" + toString(mod->id);

    std::thread email_exchage_thread(curlwrapper::put, call_number, url, headers, add_mod_handler->curlform_copycontents, &onModAdded);
    email_exchage_thread.detach();
  }

  void addMod(ModHandler* add_mod_handler, function<void(int response_code, string message, Mod* mod)> callback)
  {
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    add_mod_callback[call_number] = new AddModParams;
    add_mod_callback[call_number]->callback = callback;

    string url = "https://api.mod.works/v1/games/" + toString(game_id) + "/mods";

    std::thread add_mod_thread(curlwrapper::postForm, call_number, url, headers, add_mod_handler->curlform_copycontents, add_mod_handler->curlform_files, &onModAdded);
    add_mod_thread.detach();
  }

  void onModDeleted(int call_number, int response_code, string message, json response)
  {
    Mod* mod = new Mod(response);
    delete_mod_callbacks[call_number]->callback(response_code, message, mod);
    delete_mod_callbacks.erase(call_number);
  }

  void deleteMod(Mod* mod, function<void(int response_code, string message, Mod* mod)> callback)
  {
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    delete_mod_callbacks[call_number] = new DeleteModParams;
    delete_mod_callbacks[call_number]->callback = callback;

    string url = "https://api.mod.works/v1/games/" + toString(game_id) + "/mods/" + toString(mod->id);

    std::thread email_exchage_thread(curlwrapper::deleteCall, call_number, url, headers, &onModDeleted);
    email_exchage_thread.detach();
  }

  void onFileAdded(int call_number, int response_code, string message, json response)
  {
    add_file_callbacks[call_number]->callback(200, message, add_file_callbacks[call_number]->mod);
    add_file_callbacks.erase(call_number);
  }

  void addModfile(Mod *mod, ModfileHandler* add_mod_file_handler, function<void(int response_code, string message, Mod* mod)> callback)
  {
    minizipwrapper::compress(add_mod_file_handler->path, getModIODirectory() + "tmp/modfile.zip");
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");
    string url = string("https://api.mod.works/v1/games/") + toString(7) + "/mods/" + toString(mod->id) + "/files";

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    add_file_callbacks[call_number] = new AddFileParams;
    add_file_callbacks[call_number]->mod = mod;
    add_file_callbacks[call_number]->callback = callback;

    map<string, string> curlform_files;
    curlform_files["filedata"] = getModIODirectory() + "tmp/modfile.zip";

    std::thread add_file_thread(curlwrapper::postForm, call_number, url, headers, add_mod_file_handler->curlform_copycontents, curlform_files, &onFileAdded);
    add_file_thread.detach();
  }


  void onImageDownloaded(int call_number, int response_code, string message, string url, string path)
  {
    download_image_callbacks[call_number]->callback(response_code, message, download_image_callbacks[call_number]->mod, path);
    download_image_callbacks.erase(call_number);
  }

  void downloadModLogoThumbnail(Mod *mod, function< void(int response_code, string message, Mod* mod, string path) > callback)
  {
    string file_path = string(getModIODirectory() + "images/") + toString(mod->id) + "_mod_logo_thumb.png";

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    download_image_callbacks[call_number] = new DownloadImageParams;
    download_image_callbacks[call_number]->mod = mod;
    download_image_callbacks[call_number]->callback = callback;

    std::thread download_image_thread(curlwrapper::download, call_number, mod->logo->thumbnail, file_path, &onImageDownloaded);

    download_image_thread.detach();
  }

  void downloadModLogoFull(Mod *mod, function< void(int response_code, string message, Mod*mod, string path) > callback)
  {
    string file_path = string(getModIODirectory() + "images/") + toString(mod->id) + "_mod_logo_full.png";

    int call_number = curlwrapper::getCallCount();
    curlwrapper::advanceCallCount();

    download_image_callbacks[call_number] = new DownloadImageParams;
    download_image_callbacks[call_number]->mod = mod;
    download_image_callbacks[call_number]->callback = callback;

    std::thread download_image_thread(curlwrapper::download, call_number, mod->logo->full, file_path, &onImageDownloaded);

    download_image_thread.detach();
  }

  void onImageFromVectorDownloaded(int call_number, int response_code, string message, string url, string path)
  {
    download_images_callbacks[call_number]->images.push_back(path);
    if((int)download_images_callbacks[call_number]->images.size() == download_images_callbacks[call_number]->image_amount)
    {
      download_images_callbacks[call_number]->callback(response_code, message, download_images_callbacks[call_number]->mod, download_images_callbacks[call_number]->images);
    }
    download_images_callbacks.erase(call_number);
  }

  void downloadModMediaImagesThumbnail(Mod *mod, function< void(int response_code, string message, Mod* mod, vector<string> paths) > callback)
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
      createDirectory(string(getModIODirectory() + "images/") + toString(mod->id) + "_mod_media/");
      string file_path = string(getModIODirectory() + "images/") + toString(mod->id) + "_mod_media/" + toString(i) + "_image_thumb.png";
      std::thread download_image_thread(curlwrapper::download, call_number, mod->media->images[i]->thumbnail, file_path, &onImageFromVectorDownloaded);
      download_image_thread.detach();
    }
  }

  void downloadModMediaImagesFull(Mod *mod, function< void(int response_code, string message, Mod* mod, vector<string> paths) > callback)
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
      createDirectory(string(getModIODirectory() + "images/") + toString(mod->id) + "_mod_media/");
      string file_path = string(getModIODirectory() + "images/") + toString(mod->id) + "_mod_media/" + toString(i) + "_image_full.png";
      std::thread download_image_thread(curlwrapper::download, call_number, mod->media->images[i]->full, file_path, &onImageFromVectorDownloaded);
      download_image_thread.detach();
    }
  }

  void onModfileDownloaded(int call_number, int response_code, string message, string url, string path)
  {
    string destintation_path = download_modfile_callbacks[call_number]->destination_path;
    createDirectory(destintation_path);
    minizipwrapper::extract(path, destintation_path);
    removeFile(path);
    download_modfile_callbacks[call_number]->callback(response_code, message, download_modfile_callbacks[call_number]->mod, path);
    download_modfile_callbacks.erase(call_number);
  }

  void installMod(Mod *mod, string destination_path, function< void(int response_code, string message, Mod* mod, string path) > callback)
  {
    string file_path = string(getModIODirectory() + "tmp/") + toString(mod->modfile->id) + "_modfile.zip";

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
