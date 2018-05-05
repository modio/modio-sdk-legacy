#include "c/methods/MediaMethods.h"

extern "C"
{

void modioAddModLogo(void* object, u32 mod_id, char* logo_path, void (*callback)(void* object, ModioResponse response))
{
  u32 call_number = modio::curlwrapper::getCallNumber();

  add_mod_logo_callbacks[call_number] = new AddModLogoParams;
  add_mod_logo_callbacks[call_number]->callback = callback;
  add_mod_logo_callbacks[call_number]->object = object;

  std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/media";

  std::multimap<std::string, std::string> curlform_copycontents;
  std::map<std::string, std::string> curlform_files;
  curlform_files["logo"] = logo_path;

  modio::curlwrapper::postForm(call_number, url, modio::getHeaders(), curlform_copycontents, curlform_files, &modioOnAddModLogo);
}

void modioAddModImages(void* object, u32 mod_id, char** image_paths_array, u32 image_paths_array_size, void (*callback)(void* object, ModioResponse response))
{
  u32 call_number = modio::curlwrapper::getCallNumber();

  add_mod_images_callbacks[call_number] = new AddModImagesParams;
  add_mod_images_callbacks[call_number]->callback = callback;
  add_mod_images_callbacks[call_number]->object = object;

  std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/media";

  std::multimap<std::string, std::string> curlform_copycontents;
  std::map<std::string, std::string> curlform_files;

  for(int i=0; i<image_paths_array_size; i++)
  {
      curlform_files["image" + modio::toString(i+1)] = image_paths_array[i];
  }

  modio::curlwrapper::postForm(call_number, url, modio::getHeaders(), curlform_copycontents, curlform_files, &modioOnAddModImages);
}

void modioAddModYoutubeLinks(void* object, u32 mod_id, char** youtube_links_array, u32 youtube_links_array_size, void (*callback)(void* object, ModioResponse response))
{
  u32 call_number = modio::curlwrapper::getCallNumber();

  add_mod_youtube_links_callbacks[call_number] = new AddModYoutubeLinksParams;
  add_mod_youtube_links_callbacks[call_number]->callback = callback;
  add_mod_youtube_links_callbacks[call_number]->object = object;

  std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/media";

  std::multimap<std::string, std::string> curlform_copycontents;
  std::map<std::string, std::string> curlform_files;

  for(int i=0; i<youtube_links_array_size; i++)
  {
      curlform_files["youtube[]"] = youtube_links_array[i];
  }

  modio::curlwrapper::postForm(call_number, url, modio::getHeaders(), curlform_copycontents, curlform_files, &modioOnAddModYoutubeLinks);
}

void modioAddModSketchfabLinks(void* object, u32 mod_id, char** sketchfab_links_array, u32 sketchfab_links_array_size, void (*callback)(void* object, ModioResponse response))
{
  u32 call_number = modio::curlwrapper::getCallNumber();

  add_mod_sketchfab_links_callbacks[call_number] = new AddModSketchfabLinksParams;
  add_mod_sketchfab_links_callbacks[call_number]->callback = callback;
  add_mod_sketchfab_links_callbacks[call_number]->object = object;

  std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/media";

  std::multimap<std::string, std::string> curlform_copycontents;
  std::map<std::string, std::string> curlform_files;

  for(int i=0; i<sketchfab_links_array_size; i++)
  {
      curlform_files["sketchfab[]"] = sketchfab_links_array[i];
  }

  modio::curlwrapper::postForm(call_number, url, modio::getHeaders(), curlform_copycontents, curlform_files, &modioOnAddModSketchfabLinks);
}

}
