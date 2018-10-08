#include "c++/schemas/Avatar.h"

namespace modio
{
void Avatar::initialize(ModioAvatar modio_avatar)
{
  if (modio_avatar.filename)
    this->filename = modio_avatar.filename;
  if (modio_avatar.original)
    this->original = modio_avatar.original;
  if (modio_avatar.thumb_50x50)
    this->thumb_50x50 = modio_avatar.thumb_50x50;
  if (modio_avatar.thumb_100x100)
    this->thumb_100x100 = modio_avatar.thumb_100x100;
}

nlohmann::json toJson(Avatar &avatar)
{
  nlohmann::json avatar_json;

  avatar_json["filename"] = avatar.filename;
  avatar_json["original"] = avatar.original;
  avatar_json["thumb_50x50"] = avatar.thumb_50x50;
  avatar_json["thumb_100x100"] = avatar.thumb_100x100;

  return avatar_json;
}
} // namespace modio
