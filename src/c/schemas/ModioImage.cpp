#include "c/schemas/ModioImage.h"
#include "Utility.h"                // for hasKey
#include "c/ModioC.h"               // for ModioDownload

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

  void modioInitImageCpp(ModioImage* modio_image, modio::Image* image)
  {
    modio_image->filename = new char[image->filename.size() + 1];
    strcpy(modio_image->filename, image->filename.c_str());

    modio_image->original = new char[image->original.size() + 1];
    strcpy(modio_image->original, image->original.c_str());

    modio_image->thumb_320x180 = new char[image->thumb_320x180.size() + 1];
    strcpy(modio_image->thumb_320x180, image->thumb_320x180.c_str());
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
