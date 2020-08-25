#include "Filesystem.h"
#include <iostream>

namespace modio
{
  bool GenericFilesystem::IsDir(const ::std::string& dir)
  {
    return Filesystem::DirExists(dir);
  }
}