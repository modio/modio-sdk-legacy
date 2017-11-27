#ifndef MODIO_MEDIA_H
#define MODIO_MEDIA_H

#include "data_containers/ModioMedia.h"
#include "Globals.h"
#include "instance_data_containers/Image.h"

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
