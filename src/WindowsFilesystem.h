#ifndef MODIO_WINDOWS_FILESYSTEM_H
#define MODIO_WINDOWS_FILESYSTEM_H

#include "Filesystem.h"

namespace modio
{
  namespace windows_platform
  {
    std::ofstream ofstream(const std::string& path, std::ios_base::openmode mode = std::ios_base::out );
    std::ifstream ifstream(const std::string& path, std::ios_base::openmode mode = std::ios_base::in );
    FILE* fopen(const char* path, const char* mode);
  }
}

#endif
