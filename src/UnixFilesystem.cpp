#include "UnixFilesystem.h"

#if defined(MODIO_OSX_DETECTED) || defined(MODIO_LINUX_DETECTED)
namespace modio
{
  namespace unix_platform
  {
    std::ofstream ofstream(const std::string& path, std::ios_base::openmode mode /*= std::ios_base::out*/ )
    {
      return std::ofstream(path.c_str(), mode);
    }
    
    std::ifstream ifstream(const std::string& path, std::ios_base::openmode mode /*= std::ios_base::in*/ )
    {
      return std::ifstream(path.c_str(), mode);
    }
    
    FILE* fopen(const char* path, const char* mode)
    {
      return ::fopen(path, mode);
    }
  }
}
#endif
