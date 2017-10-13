#include "data_containers/Image.h"

namespace modio
{
  void initImage(Image* image, json image_json)
  {
    image->full = "";
    if(hasKey(image_json, "full"))
      image->full = image_json["full"];

    image->thumbnail = "";
    if(hasKey(image_json, "thumbnail"))
      image->thumbnail = image_json["thumbnail"];

    image->filename = "";
    if(hasKey(image_json, "filename"))
      image->filename = image_json["filename"];
  }

  void freeImage(Image* image)
  {
    delete image;
  }
}
