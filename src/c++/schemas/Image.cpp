#include "c++/schemas/Image.h"

namespace modio
{
  void Image::initialize(ModioImage modio_image)
  {
    if(modio_image.filename)
      this->filename = modio_image.filename;
    if(modio_image.original)
      this->original = modio_image.original;
    if(modio_image.thumb_320x180)
      this->thumb_320x180 = modio_image.thumb_320x180;
  }
}
