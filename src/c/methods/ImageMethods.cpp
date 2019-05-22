#include "c/methods/ImageMethods.h"https://github.com/modio/SDK/pull/82/conflict?name=include%252Fc%252FModioC.h&ancestor_oid=13b5beb0b9435710bca4288601022ace6146e3ac&base_oid=2d3e931a8ccc793fc86b6abc9b207f60e8de2e24&head_oid=e35d494931f902867378f1745ade1ebcb18ec7e4

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
