#include "exported_methods/ImageMethods.h"

extern "C"
{
  struct DownloadImageParams
  {
    void (*callback)(ModioResponse* response, char* path);
  };

  struct EditModLogoParams
  {
    int mod_id;
    void (*callback)(ModioResponse* response, int mod_id);
  };

  map< int, DownloadImageParams* > download_image_callbacks;
  map< int, EditModLogoParams* > edit_mod_logo_callbacks;

  void onImageDownloaded(int call_number, ModioResponse* response, string url, string path)
  {
    char* path_char = new char[path.size() +1];
    strcpy(path_char, path.c_str());
    download_image_callbacks[call_number]->callback(response, path_char);
    download_image_callbacks.erase(call_number);
  }

  void modioDownloadImage(char* image_url, char* path, void (*callback)(ModioResponse* response, char* path))
  {
    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    download_image_callbacks[call_number] = new DownloadImageParams;
    download_image_callbacks[call_number]->callback = callback;

    std::thread download_image_thread(modio::curlwrapper::download, call_number, image_url, path, &onImageDownloaded);
    download_image_thread.detach();
  }

  void onModLogoEdited(int call_number, ModioResponse* response, json response_json)
  {
    edit_mod_logo_callbacks[call_number]->callback(response, edit_mod_logo_callbacks[call_number]->mod_id);
    edit_mod_logo_callbacks.erase(call_number);
  }

  void modioEditModLogo(int mod_id, char* path, void (*callback)(ModioResponse* response, int mod_id))
  {
    vector<string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    edit_mod_logo_callbacks[call_number] = new EditModLogoParams;
    edit_mod_logo_callbacks[call_number]->callback = callback;
    edit_mod_logo_callbacks[call_number]->mod_id = mod_id;

    string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/media";

    multimap<string, string> curlform_copycontents;
    map<string, string> curlform_files;
    curlform_files["logo"] = path;

    std::thread add_mod_thread(modio::curlwrapper::postForm, call_number, url, headers, curlform_copycontents, curlform_files, &onModLogoEdited);
    add_mod_thread.detach();
  }
}
