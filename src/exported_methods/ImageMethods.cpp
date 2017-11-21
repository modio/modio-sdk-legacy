#include "exported_methods/ImageMethods.h"

extern "C"
{
  struct DownloadImageParams
  {
    void* object;
    std::string destination_path;
    FILE* file;
    void (*callback)(void* object, ModioResponse response, char* path);
  };

  struct EditModLogoParams
  {
    void* object;
    int mod_id;
    void (*callback)(void* object, ModioResponse response, int mod_id);
  };

  std::map< int, DownloadImageParams* > download_image_callbacks;
  std::map< int, EditModLogoParams* > edit_mod_logo_callbacks;

  void onImageDownloaded(int call_number, int response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    char* path_char = new char[download_image_callbacks[call_number]->destination_path.size() +1];
    strcpy(path_char, download_image_callbacks[call_number]->destination_path.c_str());
    fclose(download_image_callbacks[call_number]->file);
    download_image_callbacks[call_number]->callback(download_image_callbacks[call_number]->object, response, path_char);
    download_image_callbacks.erase(call_number);
  }

  void modioDownloadImage(void* object, char* image_url, char* path, void (*callback)(void* object, ModioResponse response, char* path))
  {
    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    download_image_callbacks[call_number] = new DownloadImageParams;
    download_image_callbacks[call_number]->callback = callback;
    download_image_callbacks[call_number]->destination_path = path;
    download_image_callbacks[call_number]->object = object;

    FILE* file;
    curl_off_t progress = modio::curlwrapper::getProgressIfStored(path);
    if(progress != 0)
    {
      file = fopen(path,"ab");
    }else
    {
      file = fopen(path,"wb");
    }
    download_image_callbacks[call_number]->file = file;

    modio::curlwrapper::download(call_number, image_url, path, file, progress, &onImageDownloaded);
  }

  void onModLogoEdited(int call_number, int response_code, json response_json)
  {
    ModioResponse response;
    modioInitResponse(&response, response_json);
    response.code = response_code;

    edit_mod_logo_callbacks[call_number]->callback(edit_mod_logo_callbacks[call_number]->object, response, edit_mod_logo_callbacks[call_number]->mod_id);
    edit_mod_logo_callbacks.erase(call_number);
  }

  void modioEditModLogo(void* object, int mod_id, char* path, void (*callback)(void* object, ModioResponse response, int mod_id))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);

    int call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    edit_mod_logo_callbacks[call_number] = new EditModLogoParams;
    edit_mod_logo_callbacks[call_number]->callback = callback;
    edit_mod_logo_callbacks[call_number]->mod_id = mod_id;
    edit_mod_logo_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/media";

    std::multimap<std::string, std::string> curlform_copycontents;
    std::map<std::string, std::string> curlform_files;
    curlform_files["logo"] = path;

    modio::curlwrapper::postForm(call_number, url, headers, curlform_copycontents, curlform_files, &onModLogoEdited);
  }
}
