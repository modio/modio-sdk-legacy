#include "c++/schemas/Logo.h"

namespace modio
{
  void Logo::initialize(ModioLogo modio_iogo)
  {
    if(modio_iogo.filename)
      this->filename = modio_iogo.filename;
    if(modio_iogo.original)
      this->original = modio_iogo.original;
    if(modio_iogo.thumb_320x180)
      this->thumb_320x180 = modio_iogo.thumb_320x180;
    if(modio_iogo.thumb_640x360)
      this->thumb_640x360 = modio_iogo.thumb_640x360;
    if(modio_iogo.thumb_1280x720)
      this->thumb_1280x720 = modio_iogo.thumb_1280x720;
  }

  nlohmann::json Logo::toJson()
  {
    nlohmann::json logo_json;

    logo_json["filename"] = this->filename;
    logo_json["original"] = this->original;
    logo_json["thumb_320x180"] = this->thumb_320x180;
    logo_json["thumb_640x360"] = this->thumb_640x360;
    logo_json["thumb_1280x720"] = this->thumb_1280x720;

    return logo_json;
  }
}
