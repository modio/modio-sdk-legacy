#include "c/methods/ImageMethods.h"

extern "C"
{
  void modioDownloadImage(void *object, char const *image_url, char const *path, void (*callback)(void *object, ModioResponse modioresponse))
  {
    if (!modio::directoryExists(modio::getDirectoryPath(path)))
    {
      modio::writeLogLine("Could not open image directory: " + modio::getDirectoryPath(path), MODIO_DEBUGLEVEL_ERROR);
      modio::handleDownloadImageError(object, callback);
      return;
    }

    FILE *file = fopen(path, "wb");
    if (!file)
    {
      modio::writeLogLine("Could not open image file: " + std::string(path), MODIO_DEBUGLEVEL_ERROR);
      modio::handleDownloadImageError(object, callback);
      return;
    }

    u32 call_number = modio::curlwrapper::getCallNumber();
    download_image_callbacks[call_number] = new DownloadImageParams;
    download_image_callbacks[call_number]->callback = callback;
    download_image_callbacks[call_number]->destination_path = path;
    download_image_callbacks[call_number]->object = object;
    download_image_callbacks[call_number]->file = file;

    modio::curlwrapper::download(call_number, modio::getHeaders(), image_url, path, file, &modioOnImageDownloaded);
  }
}
