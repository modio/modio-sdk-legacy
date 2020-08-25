#ifndef MODIO_UNIX_FILESYSTEM_H
#define MODIO_UNIX_FILESYSTEM_H

namespace modio
{
  struct UnixFilesystem
  {
    /**
     * Checks if a directory exists, if it's a file, it will return false
     */
    static bool DirExists(const std::string& directory);

    static bool CreateDir(const std::string& directory);
  };
  typedef UnixFilesystem Filesystem;
}
#endif