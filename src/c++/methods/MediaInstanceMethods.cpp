#include "c++/ModIOInstance.h"

namespace modio
{
void Instance::addModLogo(u32 mod_id, std::string logo_path, const std::function<void(const modio::Response &response)> &callback)
{
  const struct AddModLogoCall *add_mod_logo_call = new AddModLogoCall{callback};
  add_mod_logo_calls[this->current_call_id] = (AddModLogoCall *)add_mod_logo_call;

  modioAddModLogo((void *)new u32(this->current_call_id), mod_id, (char *)logo_path.c_str(), &onAddModLogo);

  this->current_call_id++;
}

void Instance::addModImages(u32 mod_id, std::vector<std::string> image_paths, const std::function<void(const modio::Response &response)> &callback)
{
  char **image_paths_array = new char *[image_paths.size()];
  for (int i = 0; i < (int)image_paths.size(); i++)
  {
    image_paths_array[i] = new char[image_paths[i].size() + 1];
    strcpy(image_paths_array[i], (char *)image_paths[i].c_str());
  }

  const struct AddModImagesCall *add_mod_images_call = new AddModImagesCall{callback};
  add_mod_images_calls[this->current_call_id] = (AddModImagesCall *)add_mod_images_call;

  modioAddModImages((void *)new u32(this->current_call_id), mod_id, image_paths_array, (u32)image_paths.size(), &onAddModImages);

  this->current_call_id++;

  for (int i = 0; i < (int)image_paths.size(); i++)
    delete[] image_paths_array[i];
  delete[] image_paths_array;
}

void Instance::addModYoutubeLinks(u32 mod_id, std::vector<std::string> youtube_links, const std::function<void(const modio::Response &response)> &callback)
{
  char **youtube_links_array = new char *[youtube_links.size()];
  for (int i = 0; i < (int)youtube_links.size(); i++)
  {
    youtube_links_array[i] = new char[youtube_links[i].size() + 1];
    strcpy(youtube_links_array[i], (char *)youtube_links[i].c_str());
  }

  const struct AddModYoutubeLinksCall *add_mod_youtube_links_call = new AddModYoutubeLinksCall{callback};
  add_mod_youtube_links_calls[this->current_call_id] = (AddModYoutubeLinksCall *)add_mod_youtube_links_call;

  modioAddModYoutubeLinks((void *)new u32(this->current_call_id), mod_id, youtube_links_array, (u32)youtube_links.size(), &onAddModYoutubeLinks);

  this->current_call_id++;

  for (int i = 0; i < (int)youtube_links.size(); i++)
    delete[] youtube_links_array[i];
  delete[] youtube_links_array;
}

void Instance::addModSketchfabLinks(u32 mod_id, std::vector<std::string> sketchfab_links, const std::function<void(const modio::Response &response)> &callback)
{
  char **sketchfab_links_array = new char *[sketchfab_links.size()];
  for (int i = 0; i < (int)sketchfab_links.size(); i++)
  {
    sketchfab_links_array[i] = new char[sketchfab_links[i].size() + 1];
    strcpy(sketchfab_links_array[i], (char *)sketchfab_links[i].c_str());
  }

  const struct AddModSketchfabLinksCall *add_mod_sketchfab_links_call = new AddModSketchfabLinksCall{callback};
  add_mod_sketchfab_links_calls[this->current_call_id] = (AddModSketchfabLinksCall *)add_mod_sketchfab_links_call;

  modioAddModSketchfabLinks((void *)new u32(this->current_call_id), mod_id, sketchfab_links_array, (u32)sketchfab_links.size(), &onAddModSketchfabLinks);

  for (int i = 0; i < (int)sketchfab_links.size(); i++)
    delete[] sketchfab_links_array[i];
  delete[] sketchfab_links_array;

  this->current_call_id++;
}

void Instance::deleteModImages(u32 mod_id, std::vector<std::string> image_paths, const std::function<void(const modio::Response &response)> &callback)
{
  char **image_paths_array = new char *[image_paths.size()];
  for (int i = 0; i < (int)image_paths.size(); i++)
  {
    image_paths_array[i] = new char[image_paths[i].size() + 1];
    strcpy(image_paths_array[i], (char *)image_paths[i].c_str());
  }

  const struct DeleteModImagesCall *delete_mod_images_call = new DeleteModImagesCall{callback};
  delete_mod_images_calls[this->current_call_id] = (DeleteModImagesCall *)delete_mod_images_call;

  modioDeleteModImages((void *)new u32(this->current_call_id), mod_id, image_paths_array, (u32)image_paths.size(), &onDeleteModImages);

  this->current_call_id++;

  for (int i = 0; i < (int)image_paths.size(); i++)
    delete[] image_paths_array[i];
  delete[] image_paths_array;
}

void Instance::deleteModYoutubeLinks(u32 mod_id, std::vector<std::string> youtube_links, const std::function<void(const modio::Response &response)> &callback)
{
  char **youtube_links_array = new char *[youtube_links.size()];
  for (int i = 0; i < (int)youtube_links.size(); i++)
  {
    youtube_links_array[i] = new char[youtube_links[i].size() + 1];
    strcpy(youtube_links_array[i], (char *)youtube_links[i].c_str());
  }

  const struct DeleteModYoutubeLinksCall *delete_mod_youtube_links_call = new DeleteModYoutubeLinksCall{callback};
  delete_mod_youtube_links_calls[this->current_call_id] = (DeleteModYoutubeLinksCall *)delete_mod_youtube_links_call;

  modioDeleteModYoutubeLinks((void *)new u32(this->current_call_id), mod_id, youtube_links_array, (u32)youtube_links.size(), &onDeleteModYoutubeLinks);

  this->current_call_id++;

  for (int i = 0; i < (int)youtube_links.size(); i++)
    delete[] youtube_links_array[i];
  delete[] youtube_links_array;
}

void Instance::deleteModSketchfabLinks(u32 mod_id, std::vector<std::string> sketchfab_links, const std::function<void(const modio::Response &response)> &callback)
{
  char **sketchfab_links_array = new char *[sketchfab_links.size()];
  for (int i = 0; i < (int)sketchfab_links.size(); i++)
  {
    sketchfab_links_array[i] = new char[sketchfab_links[i].size() + 1];
    strcpy(sketchfab_links_array[i], (char *)sketchfab_links[i].c_str());
  }

  const struct DeleteModSketchfabLinksCall *delete_mod_sketchfab_links_call = new DeleteModSketchfabLinksCall{callback};
  delete_mod_sketchfab_links_calls[this->current_call_id] = (DeleteModSketchfabLinksCall *)delete_mod_sketchfab_links_call;

  modioDeleteModSketchfabLinks((void *)new u32(this->current_call_id), mod_id, sketchfab_links_array, (u32)sketchfab_links.size(), &onDeleteModSketchfabLinks);

  this->current_call_id++;

  for (int i = 0; i < (int)sketchfab_links.size(); i++)
    delete[] sketchfab_links_array[i];
  delete[] sketchfab_links_array;
}
} // namespace modio
