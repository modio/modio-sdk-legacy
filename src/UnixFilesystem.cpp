#include "Filesystem.h"

#if defined(MODIO_LINUX_DETECTED) || defined(MODIO_OSX_DETECTED)
namespace modio
{
  bool UnixFilesystem::DirectoryExists(const std::string& directory)
  {
    if (path == "")
      return true;
    DIR* dir = opendir(modio::addSlashIfNeeded(path).c_str());
    if (dir)
    {
      closedir(dir);
      return true;
    }

    return false;
  }

  bool UnixFilesystem::CreateDirectory(const std::string& directory)
  {
    errno = 0;
    if (mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0))
    {
    // ERROR_ALREADY_EXISTS is returned if a FILE or folder exists, ensure that it's a folder, else
    // we can't create subdirectories
    if (!(errno == EEXIST && modio::directoryExists(directory))
    {
      writeLogLine("Failed to create directory [" + directory + "] with error: " + strerror(errno), MODIO_DEBUGLEVEL_LOG);
        return false;
    }
    }
    return true;
  }
};
#endif