#include "data_containers/Image.h"

extern "C"
{
  void modioInitImage(ModioImage* image, json image_json)
  {
    image->full = "";
    if(modio::hasKey(image_json, "full"))
      image->full = image_json["full"];

    image->thumbnail = "";
    if(modio::hasKey(image_json, "thumbnail"))
      image->thumbnail = image_json["thumbnail"];

    image->filename = "";
    if(modio::hasKey(image_json, "filename"))
      image->filename = image_json["filename"];
  }

  void modioFreeImage(ModioImage* image)
  {
    delete image;
  }
}
