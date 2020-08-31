#ifndef MODIO_UNIX_FILESYSTEM_H
#define MODIO_UNIX_FILESYSTEM_H

#include "Filesystem.h"

namespace modio
{
  namespace unix_platform
  {
    std::ofstream ofstream(const std::string& path, std::ios_base::openmode mode = std::ios_base::out );
    std::ifstream ifstream(const std::string& path, std::ios_base::openmode mode = std::ios_base::in );
    FILE* fopen(const char* path, const char* mode);
  };
}

#endif
