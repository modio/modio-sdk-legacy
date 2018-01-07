#include "c++/schemas/Icon.h"

namespace modio
{
  void Icon::initialize(ModioIcon modio_icon)
  {
    if(modio_icon.filename)
      this->filename = modio_icon.filename;
    if(modio_icon.original)
      this->original = modio_icon.original;
    if(modio_icon.thumb_64x64)
      this->thumb_64x64 = modio_icon.thumb_64x64;
    if(modio_icon.thumb_128x128)
      this->thumb_128x128 = modio_icon.thumb_128x128;
    if(modio_icon.thumb_256x256)
      this->thumb_256x256 = modio_icon.thumb_256x256;
  }
}
