#ifndef MODIO_UNIX_FILESYSTEM_H
#define MODIO_UNIX_FILESYSTEM_H

#include "Filesystem.h"

namespace modio
{
  struct UnixFilesystem: public GenericFilesystem
  {
    /**
     * Checks if a directory exists, if it's a file, it will return false
     */
    static bool DirExists(const std::string& directory);

    /**
     * Creates a directory, will return true if the directory already exists or is a system drive
     */
    static bool CreateDir(const std::string& directory);
  };
  typedef UnixFilesystem Filesystem;
}
#endif