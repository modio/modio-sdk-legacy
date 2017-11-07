#include "data_containers/Image.h"

extern "C"
{
  void modioInitImage(ModioImage* image, json image_json)
  {
    image->filename = NULL;
    if(modio::hasKey(image_json, "filename"))
    {
      string filename_str = image_json["filename"];
      image->filename = new char[filename_str.size() + 1];
      strcpy(image->filename, filename_str.c_str());
    }

    image->full = NULL;
    if(modio::hasKey(image_json, "full"))
    {
      string full_str = image_json["full"];
      image->full = new char[full_str.size() + 1];
      strcpy(image->full, full_str.c_str());
    }

    image->thumb_1280x720 = NULL;
    if(modio::hasKey(image_json, "thumb_1280x720"))
    {
      string thumb_1280x720_str = image_json["thumb_1280x720"];
      image->thumb_1280x720 = new char[thumb_1280x720_str.size() + 1];
      strcpy(image->thumb_1280x720, thumb_1280x720_str.c_str());
    }

    image->thumb_640x360 = NULL;
    if(modio::hasKey(image_json, "thumb_640x360"))
    {
      string thumb_640x360_str = image_json["thumb_640x360"];
      image->thumb_640x360 = new char[thumb_640x360_str.size() + 1];
      strcpy(image->thumb_640x360, thumb_640x360_str.c_str());
    }

    image->thumb_320x180 = NULL;
    if(modio::hasKey(image_json, "thumb_320x180"))
    {
      string thumb_320x180_str = image_json["thumb_320x180"];
      image->thumb_320x180 = new char[thumb_320x180_str.size() + 1];
      strcpy(image->thumb_320x180, thumb_320x180_str.c_str());
    }
  }

  void modioFreeImage(ModioImage* image)
  {
    delete[] image->filename;
    delete[] image->full;
    delete[] image->thumb_1280x720;
    delete[] image->thumb_320x180;
    delete[] image->thumb_640x360;

    delete image;
  }
}
