#include "c/methods/ImageMethods.h"

extern "C"
{
  void modioDownloadImage(void *object, char *image_url, char *path, void (*callback)(void *object, ModioResponse modioresponse))
  {
    if (!modio::directoryExists(modio::getDirectoryPath(path)))
    {
      modio::writeLogLine("The destination directory was not found. Image won't be downloaded.", MODIO_DEBUGLEVEL_ERROR);
      ModioResponse response;
      nlohmann::json empty_json;
      modioInitResponse(&response, empty_json);
      callback(object, response);
      modioFreeResponse(&response);
      return;
    }

    u32 call_number = modio::curlwrapper::getCallNumber();

    download_image_callbacks[call_number] = new DownloadImageParams;
    download_image_callbacks[call_number]->callback = callback;
    download_image_callbacks[call_number]->destination_path = path;
    download_image_callbacks[call_number]->object = object;

    FILE *file = fopen(path, "wb");
    download_image_callbacks[call_number]->file = file;

    modio::curlwrapper::download(call_number, modio::getHeaders(), image_url, path, file, &modioOnImageDownloaded);
  }
}
