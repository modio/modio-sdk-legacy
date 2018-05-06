#include "c/methods/ImageMethods.h"

extern "C"
{
void modioDownloadImage(void *object, char *image_url, char *path, void (*callback)(void *object, ModioResponse modioresponse))
{
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
