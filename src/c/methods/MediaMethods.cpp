#include "c/methods/MediaMethods.h"

extern "C"
{

void modioAddModLogo(void* object, u32 mod_id, char const* logo_path, void (*callback)(void* object, ModioResponse response))
{
  u32 call_number = modio::curlwrapper::getCallNumber();

  add_mod_logo_callbacks[call_number] = new GenericRequestParams;
  add_mod_logo_callbacks[call_number]->callback = callback;
  add_mod_logo_callbacks[call_number]->object = object;

  std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/media";

  std::multimap<std::string, std::string> curlform_copycontents;
  std::map<std::string, std::string> curlform_files;
  curlform_files["logo"] = logo_path;

  modio::curlwrapper::postForm(call_number, url, modio::getHeaders(), curlform_copycontents, curlform_files, &modioOnAddModLogo);
}

void modioAddModImages(void* object, u32 mod_id, char const* const* image_paths_array, u32 image_paths_array_size, void (*callback)(void* object, ModioResponse response))
{
  u32 call_number = modio::curlwrapper::getCallNumber();

  add_mod_images_callbacks[call_number] = new GenericRequestParams;
  add_mod_images_callbacks[call_number]->callback = callback;
  add_mod_images_callbacks[call_number]->object = object;

  std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/media";

  std::multimap<std::string, std::string> curlform_copycontents;
  std::map<std::string, std::string> curlform_files;

  for(u32 i=0; i<image_paths_array_size; i++)
  {
      curlform_files["image" + modio::toString(i+1)] = image_paths_array[i];
  }

  modio::curlwrapper::postForm(call_number, url, modio::getHeaders(), curlform_copycontents, curlform_files, &modioOnAddModImages);
}

void modioAddModYoutubeLinks(void* object, u32 mod_id, char const* const* youtube_links_array, u32 youtube_links_array_size, void (*callback)(void* object, ModioResponse response))
{
  std::map<std::string, std::string> data;
  u32 call_number = modio::curlwrapper::getCallNumber();

  add_mod_youtube_links_callbacks[call_number] = new GenericRequestParams;
  add_mod_youtube_links_callbacks[call_number]->callback = callback;
  add_mod_youtube_links_callbacks[call_number]->object = object;

  std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/media";

  for(u32 i=0; i<youtube_links_array_size; i++)
  {
      data["youtube[]"] = youtube_links_array[i];
  }

  modio::curlwrapper::post(call_number, url, modio::getHeaders(), data, &modioOnAddModYoutubeLinks);
}

void modioAddModSketchfabLinks(void* object, u32 mod_id, char const* const* sketchfab_links_array, u32 sketchfab_links_array_size, void (*callback)(void* object, ModioResponse response))
{
  std::map<std::string, std::string> data;
  u32 call_number = modio::curlwrapper::getCallNumber();

  add_mod_sketchfab_links_callbacks[call_number] = new GenericRequestParams;
  add_mod_sketchfab_links_callbacks[call_number]->callback = callback;
  add_mod_sketchfab_links_callbacks[call_number]->object = object;

  std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/media";

  for(u32 i=0; i<sketchfab_links_array_size; i++)
  {
      data["sketchfab[]"] = sketchfab_links_array[i];
  }

  modio::curlwrapper::post(call_number, url, modio::getHeaders(), data, &modioOnAddModSketchfabLinks);
}

void modioDeleteModImages(void* object, u32 mod_id, char const* const* image_paths_array, u32 image_paths_array_size, void (*callback)(void* object, ModioResponse response))
{
  std::map<std::string, std::string> data;
  u32 call_number = modio::curlwrapper::getCallNumber();

  delete_mod_images_callbacks[call_number] = new GenericRequestParams;
  delete_mod_images_callbacks[call_number]->callback = callback;
  delete_mod_images_callbacks[call_number]->object = object;

  std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/media";

  for(u32 i=0; i<image_paths_array_size; i++)
  {
    data["images[]"] = image_paths_array[i];
  }

  modio::curlwrapper::deleteCall(call_number, url, modio::getUrlEncodedHeaders(), data, &modioOnDeleteModImages);
}

void modioDeleteModYoutubeLinks(void* object, u32 mod_id, char const* const* youtube_links_array, u32 youtube_links_array_size, void (*callback)(void* object, ModioResponse response))
{
  std::map<std::string, std::string> data;
  u32 call_number = modio::curlwrapper::getCallNumber();

  delete_mod_youtube_links_callbacks[call_number] = new GenericRequestParams;
  delete_mod_youtube_links_callbacks[call_number]->callback = callback;
  delete_mod_youtube_links_callbacks[call_number]->object = object;

  std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/media";

  for(u32 i=0; i<youtube_links_array_size; i++)
  {
    data["youtube[]"] = youtube_links_array[i];
  }

  modio::curlwrapper::deleteCall(call_number, url, modio::getUrlEncodedHeaders(), data, &modioOnDeleteModYoutubeLinks);
}

void modioDeleteModSketchfabLinks(void* object, u32 mod_id, char const* const* sketchfab_links_array, u32 sketchfab_links_array_size, void (*callback)(void* object, ModioResponse response))
{
  std::map<std::string, std::string> data;
  u32 call_number = modio::curlwrapper::getCallNumber();

  delete_mod_sketchfab_links_callbacks[call_number] = new GenericRequestParams;
  delete_mod_sketchfab_links_callbacks[call_number]->callback = callback;
  delete_mod_sketchfab_links_callbacks[call_number]->object = object;

  std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/media";

  for(u32 i=0; i<sketchfab_links_array_size; i++)
  {
    data["sketchfab[]"] = sketchfab_links_array[i];
  }

  modio::curlwrapper::deleteCall(call_number, url, modio::getUrlEncodedHeaders(), data, &modioOnDeleteModSketchfabLinks);
}

}
