#include "c++/schemas/Media.h"

namespace modio
{
void Media::initialize(ModioMedia modio_media)
{
  this->youtube.resize(modio_media.youtube_size);
  for (u32 i = 0; i < modio_media.youtube_size; i++)
  {
    this->youtube[i] = modio_media.youtube_array[i];
  }

  this->sketchfab.resize(modio_media.sketchfab_size);
  for (u32 i = 0; i < modio_media.sketchfab_size; i++)
  {
    this->sketchfab[i] = modio_media.sketchfab_array[i];
  }

  this->images.resize(modio_media.images_size);
  for (u32 i = 0; i < modio_media.images_size; i++)
  {
    this->images[i].initialize(modio_media.images_array[i]);
  }
}

nlohmann::json toJson(Media &media)
{
  nlohmann::json media_json;

  nlohmann::json youtube_json;
  for (auto &youtube_str : media.youtube)
  {
    youtube_json.push_back(youtube_str);
  }
  media_json["youtube"] = youtube_json;

  nlohmann::json sketchfab_json;
  for (auto &sketchfab_str : media.sketchfab)
  {
    sketchfab_json.push_back(sketchfab_str);
  }
  media_json["sketchfab"] = sketchfab_json;

  nlohmann::json images_json;
  for (auto &images_img : media.images)
  {
    images_json.push_back(modio::toJson(images_img));
  }
  media_json["images"] = images_json;

  return media_json;
}
} // namespace modio
