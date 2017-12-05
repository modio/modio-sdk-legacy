#ifndef MODIO_MEDIA_H
#define MODIO_MEDIA_H

#include "extern_c/schemas/ModioMedia.h"
#include "instance/schemas/Image.h"
#include "Globals.h"

namespace modio
{
  class Media
  {
  public:
    std::vector<std::string> youtube;
    std::vector<std::string> sketchfab;
    std::vector<Image> images;

    void initialize(ModioMedia media);
  };
}

#endif
