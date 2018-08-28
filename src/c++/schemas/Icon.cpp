#include "c++/schemas/Icon.h"

namespace modio
{
  void Icon::initialize(ModioIcon modio_icon)
  {
    if(modio_icon.filename)
      this->filename = modio_icon.filename;
    if(modio_icon.original)
      this->original = modio_icon.original;
    if(modio_icon.thumb_64x64)
      this->thumb_64x64 = modio_icon.thumb_64x64;
    if(modio_icon.thumb_128x128)
      this->thumb_128x128 = modio_icon.thumb_128x128;
    if(modio_icon.thumb_256x256)
      this->thumb_256x256 = modio_icon.thumb_256x256;
  }

  nlohmann::json Icon::toJson()
  {
    nlohmann::json icon_json;

    icon_json["filename"] = this->filename;
    icon_json["original"] = this->original;
    icon_json["thumb_64x64"] = this->thumb_64x64;
    icon_json["thumb_128x128"] = this->thumb_128x128;
    icon_json["thumb_256x256"] = this->thumb_256x256;

    return icon_json;
  }
}
