#include "exported_methods/ImageMethods.h"

extern "C"
{
  struct DownloadImageParams
  {
    void (*callback)(ModioResponse* response, char* path);
  };

  map< int, DownloadImageParams* > download_image_callbacks;

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
}
