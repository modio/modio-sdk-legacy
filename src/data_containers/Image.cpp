#include "data_containers/Image.h"

extern "C"
{
  void modioInitImage(ModioImage* image, json image_json)
  {
    image->full = NULL;
    if(modio::hasKey(image_json, "full"))
    {
      string full_str = image_json["full"];
      image->full = new char[full_str.size() + 1];
      strcpy(image->full, full_str.c_str());
    }

    image->thumbnail = NULL;
    if(modio::hasKey(image_json, "thumbnail"))
    {
      string thumbnail_str = image_json["thumbnail"];
      image->thumbnail = new char[thumbnail_str.size() + 1];
      strcpy(image->thumbnail, thumbnail_str.c_str());
    }

    image->filename = NULL;
    if(modio::hasKey(image_json, "filename"))
    {
      string filename_str = image_json["filename"];
      image->filename = new char[filename_str.size() + 1];
      strcpy(image->filename, filename_str.c_str());
    }
  }

  void modioFreeImage(ModioImage* image)
  {
    delete image;
  }
}
