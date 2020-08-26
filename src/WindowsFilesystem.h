#ifndef MODIO_WINDOWS_FILESYSTEM_H
#define MODIO_WINDOWS_FILESYSTEM_H

#include <string>
#include <vector>

namespace modio
{
  struct WindowsFilesystem : public GenericFilesystem
  {
    /**
     * Checks if a directory exists, if it's a file, it will return false
     */
    static bool DirExists(const std::string& dir );

    /**
     * Won't return . and ..
     */
    static std::vector<std::string> GetItemsInDir(const std::string& dir);

    /**
     * Creates a directory, will return true if the directory already exists or is a system drive
     */
    //static bool CreateDir(const std::string& dir);
  private:
    /**
     * Checks if the provided path is directly to a drive path
     */
    static bool IsDrive(const std::string& path);
  };
  typedef WindowsFilesystem Filesystem;
}

#endif