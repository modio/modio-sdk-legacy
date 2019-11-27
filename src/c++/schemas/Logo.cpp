#include "c++/schemas/Logo.h"
#include "c/ModioC.h"                      // for ModioLogo
#include "dependencies/nlohmann/json.hpp"  // for json

namespace modio
{
void Logo::initialize(ModioLogo modio_iogo)
{
  if (modio_iogo.filename)
    filename = modio_iogo.filename;
  if (modio_iogo.original)
    original = modio_iogo.original;
  if (modio_iogo.thumb_320x180)
    thumb_320x180 = modio_iogo.thumb_320x180;
  if (modio_iogo.thumb_640x360)
    thumb_640x360 = modio_iogo.thumb_640x360;
  if (modio_iogo.thumb_1280x720)
    thumb_1280x720 = modio_iogo.thumb_1280x720;
}

nlohmann::json toJson(Logo &logo)
{
  nlohmann::json logo_json;

  logo_json["filename"] = logo.filename;
  logo_json["original"] = logo.original;
  logo_json["thumb_320x180"] = logo.thumb_320x180;
  logo_json["thumb_640x360"] = logo.thumb_640x360;
  logo_json["thumb_1280x720"] = logo.thumb_1280x720;

  return logo_json;
}
} // namespace modio
