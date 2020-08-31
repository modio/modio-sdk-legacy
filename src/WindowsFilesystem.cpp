#include "Filesystem.h"

#if defined(MODIO_WINDOWS_DETECTED)
#include <codecvt>
#include "WindowsFilesystem.h"
#endif

#if defined(MODIO_WINDOWS_DETECTED)
namespace modio
{
  namespace windows_platform
  {    
    std::ofstream ofstream(const std::string& path, std::ios_base::openmode mode /*= std::ios_base::out*/ )
    {
      return std::ofstream(utf8ToWstr(path).c_str(), mode);
    }
    
    std::ifstream ifstream(const std::string& path, std::ios_base::openmode mode /*= std::ios_base::in*/ )
    {
      return std::ifstream(utf8ToWstr(path).c_str(), mode);
    }
    
    FILE* fopen(const char* path, const char* mode)
    {
      return _wfopen(utf8ToWstr(path).c_str(), utf8ToWstr(mode).c_str());
    }

    std::wstring utf8ToWstr(const std::string& utf8_str)
    {
      return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(utf8_str);
    }

    std::string wstrToUtf8(const std::wstring& wide_string)
    {
      return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wide_string);
    }
  }
}
#endif
