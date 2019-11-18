#include "c++/ModIOInstance.h"
#include "ModioUtility.h"
#include "c++/methods/callbacks/MediaInstanceCallbacks.h"

namespace modio
{
void Instance::addModLogo(u32 mod_id, std::string logo_path, const std::function<void(const modio::Response &response)> &callback)
{
  struct GenericCall *add_mod_logo_call = new GenericCall{callback};
  add_mod_logo_calls[current_call_id] = add_mod_logo_call;

  modioAddModLogo((void*)((uintptr_t)current_call_id), mod_id, logo_path.c_str(), &onAddModLogo);

  current_call_id++;
}

void Instance::addModImages(u32 mod_id, std::vector<std::string> image_paths, const std::function<void(const modio::Response &response)> &callback)
{
  char **image_paths_array = new char *[image_paths.size()];
  for (size_t i = 0; i < image_paths.size(); i++)
  {
    image_paths_array[i] = new char[image_paths[i].size() + 1];
    strcpy(image_paths_array[i], image_paths[i].c_str());
  }

  struct GenericCall *add_mod_images_call = new GenericCall{callback};
  add_mod_images_calls[current_call_id] = add_mod_images_call;

  modioAddModImages((void*)((uintptr_t)current_call_id), mod_id, image_paths_array, (u32)image_paths.size(), &onAddModImages);

  current_call_id++;

  for (size_t i = 0; i < image_paths.size(); i++)
    delete[] image_paths_array[i];
  delete[] image_paths_array;
}

void Instance::addModYoutubeLinks(u32 mod_id, std::vector<std::string> youtube_links, const std::function<void(const modio::Response &response)> &callback)
{
  char **youtube_links_array = new char *[youtube_links.size()];
  for (size_t i = 0; i < youtube_links.size(); i++)
  {
    youtube_links_array[i] = new char[youtube_links[i].size() + 1];
    strcpy(youtube_links_array[i], youtube_links[i].c_str());
  }

  struct GenericCall *add_mod_youtube_links_call = new GenericCall{callback};
  add_mod_youtube_links_calls[current_call_id] = add_mod_youtube_links_call;

  modioAddModYoutubeLinks((void*)((uintptr_t)current_call_id), mod_id, youtube_links_array, (u32)youtube_links.size(), &onAddModYoutubeLinks);

  current_call_id++;

  for (size_t i = 0; i < youtube_links.size(); i++)
    delete[] youtube_links_array[i];
  delete[] youtube_links_array;
}

void Instance::addModSketchfabLinks(u32 mod_id, std::vector<std::string> sketchfab_links, const std::function<void(const modio::Response &response)> &callback)
{
  char **sketchfab_links_array = new char *[sketchfab_links.size()];
  for (size_t i = 0; i < sketchfab_links.size(); i++)
  {
    sketchfab_links_array[i] = new char[sketchfab_links[i].size() + 1];
    strcpy(sketchfab_links_array[i], sketchfab_links[i].c_str());
  }

  struct GenericCall *add_mod_sketchfab_links_call = new GenericCall{callback};
  add_mod_sketchfab_links_calls[current_call_id] = add_mod_sketchfab_links_call;

  modioAddModSketchfabLinks((void*)((uintptr_t)current_call_id), mod_id, sketchfab_links_array, (u32)sketchfab_links.size(), &onAddModSketchfabLinks);

  for (size_t i = 0; i < sketchfab_links.size(); i++)
    delete[] sketchfab_links_array[i];
  delete[] sketchfab_links_array;

  current_call_id++;
}

void Instance::deleteModImages(u32 mod_id, std::vector<std::string> image_paths, const std::function<void(const modio::Response &response)> &callback)
{
  char **image_paths_array = new char *[image_paths.size()];
  for (size_t i = 0; i < image_paths.size(); i++)
  {
    image_paths_array[i] = new char[image_paths[i].size() + 1];
    strcpy(image_paths_array[i], image_paths[i].c_str());
  }

  struct GenericCall *delete_mod_images_call = new GenericCall{callback};
  delete_mod_images_calls[current_call_id] = delete_mod_images_call;

  modioDeleteModImages((void*)((uintptr_t)current_call_id), mod_id, image_paths_array, (u32)image_paths.size(), &onDeleteModImages);

  current_call_id++;

  for (size_t i = 0; i < image_paths.size(); i++)
    delete[] image_paths_array[i];
  delete[] image_paths_array;
}

void Instance::deleteModYoutubeLinks(u32 mod_id, std::vector<std::string> youtube_links, const std::function<void(const modio::Response &response)> &callback)
{
  char **youtube_links_array = new char *[youtube_links.size()];
  for (size_t i = 0; i < youtube_links.size(); i++)
  {
    youtube_links_array[i] = new char[youtube_links[i].size() + 1];
    strcpy(youtube_links_array[i], youtube_links[i].c_str());
  }

  struct GenericCall *delete_mod_youtube_links_call = new GenericCall{callback};
  delete_mod_youtube_links_calls[current_call_id] = delete_mod_youtube_links_call;

  modioDeleteModYoutubeLinks((void*)((uintptr_t)current_call_id), mod_id, youtube_links_array, (u32)youtube_links.size(), &onDeleteModYoutubeLinks);

  current_call_id++;

  for (size_t i = 0; i < youtube_links.size(); i++)
    delete[] youtube_links_array[i];
  delete[] youtube_links_array;
}

void Instance::deleteModSketchfabLinks(u32 mod_id, std::vector<std::string> sketchfab_links, const std::function<void(const modio::Response &response)> &callback)
{
  char **sketchfab_links_array = new char *[sketchfab_links.size()];
  for (size_t i = 0; i < sketchfab_links.size(); i++)
  {
    sketchfab_links_array[i] = new char[sketchfab_links[i].size() + 1];
    strcpy(sketchfab_links_array[i], sketchfab_links[i].c_str());
  }

  struct GenericCall *delete_mod_sketchfab_links_call = new GenericCall{callback};
  delete_mod_sketchfab_links_calls[current_call_id] = delete_mod_sketchfab_links_call;

  modioDeleteModSketchfabLinks((void*)((uintptr_t)current_call_id), mod_id, sketchfab_links_array, (u32)sketchfab_links.size(), &onDeleteModSketchfabLinks);

  current_call_id++;

  for (size_t i = 0; i < sketchfab_links.size(); i++)
    delete[] sketchfab_links_array[i];
  delete[] sketchfab_links_array;
}
} // namespace modio
