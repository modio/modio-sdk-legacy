#ifndef MODIO_IMAGE_H
#define MODIO_IMAGE_H

#include "data_containers/ModioImage.h"
#include "Globals.h"
#include "Utility.h"

namespace modio
{
  class Image
  {
  public:
    std::string filename;
    std::string original;
    std::string thumb_1280x720;
    std::string thumb_640x360;
    std::string thumb_320x180;

    void initialize(ModioImage image);
  };
}

#endif
