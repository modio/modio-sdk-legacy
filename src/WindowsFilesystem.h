#ifndef MODIO_WINDOWS_FILESYSTEM_H
#define MODIO_WINDOWS_FILESYSTEM_H

#include "Filesystem.h"
#include <string>

namespace modio
{
  namespace windows_platform
  {
    std::ofstream ofstream(const std::string& path, std::ios_base::openmode mode = std::ios_base::out );
    std::ifstream ifstream(const std::string& path, std::ios_base::openmode mode = std::ios_base::in );
    FILE* fopen(const char* path, const char* mode);

    std::wstring utf8ToWstr(const std::string& utf8_str);
    std::string wstrToUtf8(const std::wstring& wide_string);
  }
}

#endif
