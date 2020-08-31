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
    static std::wstring WideCharFromString(std::string const& str)
    {
      return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(str);
    }

    static std::string StringFromWideChar(wchar_t const* str)
    {
      return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(str);
    }

    static std::string StringFromWideString(const std::wstring& str)
    {
      return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(str);
    }
    
    std::ofstream ofstream(const std::string& path, std::ios_base::openmode mode /*= std::ios_base::out*/ )
    {
      return std::ofstream(WideCharFromString(path).c_str(), mode);
    }
    
    std::ofstream ifstream(const std::string& path, std::ios_base::openmode mode /*= std::ios_base::in*/ )
    {
      return std::ifstream(WideCharFromString(path).c_str(), mode);
    }
    
    FILE* fopen(const char* path, const char* mode)
    {
      return _wfopen(WideCharFromString(path).c_str(), WideCharFromString(mode).c_str());
    }
  }
}
#endif
