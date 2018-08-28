#include "c/schemas/ModioIcon.h"

extern "C"
{
  void modioInitIcon(ModioIcon* icon, nlohmann::json icon_json)
  {
    icon->filename = NULL;
    if(modio::hasKey(icon_json, "filename"))
    {
      std::string filename_str = icon_json["filename"];
      icon->filename = new char[filename_str.size() + 1];
      strcpy(icon->filename, filename_str.c_str());
    }

    icon->original = NULL;
    if(modio::hasKey(icon_json, "original"))
    {
      std::string original_str = icon_json["original"];
      icon->original = new char[original_str.size() + 1];
      strcpy(icon->original, original_str.c_str());
    }

    icon->thumb_64x64 = NULL;
    if(modio::hasKey(icon_json, "thumb_64x64"))
    {
      std::string thumb_64x64_str = icon_json["thumb_64x64"];
      icon->thumb_64x64 = new char[thumb_64x64_str.size() + 1];
      strcpy(icon->thumb_64x64, thumb_64x64_str.c_str());
    }

    icon->thumb_128x128 = NULL;
    if(modio::hasKey(icon_json, "thumb_128x128"))
    {
      std::string thumb_128x128_str = icon_json["thumb_128x128"];
      icon->thumb_128x128 = new char[thumb_128x128_str.size() + 1];
      strcpy(icon->thumb_128x128, thumb_128x128_str.c_str());
    }

    icon->thumb_256x256 = NULL;
    if(modio::hasKey(icon_json, "thumb_256x256"))
    {
      std::string thumb_256x256_str = icon_json["thumb_256x256"];
      icon->thumb_256x256 = new char[thumb_256x256_str.size() + 1];
      strcpy(icon->thumb_256x256, thumb_256x256_str.c_str());
    }
  }

  void modioFreeIcon(ModioIcon* icon)
  {
    if(icon)
    {
      if(icon->filename)
        delete[] icon->filename;
      if(icon->original)
        delete[] icon->original;
      if(icon->thumb_64x64)
        delete[] icon->thumb_64x64;
      if(icon->thumb_128x128)
        delete[] icon->thumb_128x128;
      if(icon->thumb_256x256)
        delete[] icon->thumb_256x256;
    }
  }
}
