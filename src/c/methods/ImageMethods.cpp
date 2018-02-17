#include "c/methods/ImageMethods.h"

extern "C"
{
  void modioDownloadImage(void* object, char* image_url, char* path, void (*callback)(void* object, ModioResponse modioresponse))
  {
    u32 call_number = modio::curlwrapper::getCallCount();
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

    modio::curlwrapper::download(call_number, modio::getHeaders(), image_url, path, file, progress, &modioOnImageDownloaded);
  }

  void modioEditModLogo(void* object, u32 mod_id, char* path, void (*callback)(void* object, ModioResponse response, u32 mod_id))
  {
    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    edit_mod_logo_callbacks[call_number] = new EditModLogoParams;
    edit_mod_logo_callbacks[call_number]->callback = callback;
    edit_mod_logo_callbacks[call_number]->mod_id = mod_id;
    edit_mod_logo_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/media";

    std::multimap<std::string, std::string> curlform_copycontents;
    std::map<std::string, std::string> curlform_files;
    curlform_files["logo"] = path;

    modio::curlwrapper::postForm(call_number, url, modio::getHeaders(), curlform_copycontents, curlform_files, &modioOnModLogoEdited);
  }
}
