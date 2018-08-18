#include "c/schemas/ModioImage.h"

extern "C"
{
  void modioInitImage(ModioImage* image, nlohmann::json image_json)
  {
    image->filename = NULL;
    if(modio::hasKey(image_json, "filename"))
    {
      std::string filename_str = image_json["filename"];
      image->filename = new char[filename_str.size() + 1];
      strcpy(image->filename, filename_str.c_str());
    }

    image->original = NULL;
    if(modio::hasKey(image_json, "original"))
    {
      std::string original_str = image_json["original"];
      image->original = new char[original_str.size() + 1];
      strcpy(image->original, original_str.c_str());
    }

    image->thumb_320x180 = NULL;
    if(modio::hasKey(image_json, "thumb_320x180"))
    {
      std::string thumb_320x180_str = image_json["thumb_320x180"];
      image->thumb_320x180 = new char[thumb_320x180_str.size() + 1];
      strcpy(image->thumb_320x180, thumb_320x180_str.c_str());
    }
  }

  void modioFreeImage(ModioImage* image)
  {
    if(image)
    {
      if(image->filename)
        delete[] image->filename;
      if(image->original)
        delete[] image->original;
      if(image->thumb_320x180)
        delete[] image->thumb_320x180;
    }
  }
}
