#include "data_containers/Image.h"

namespace modworks
{
  Image::Image(json image_json)
  {
    this->full = "";
    if(hasKey(image_json, "full"))
      this->full = image_json["full"];

    this->thumbnail = "";
    if(hasKey(image_json, "thumbnail"))
      this->thumbnail = image_json["thumbnail"];

    this->filename = "";
    if(hasKey(image_json, "filename"))
      this->filename = image_json["filename"];
  }
}
