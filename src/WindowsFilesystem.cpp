#include "Filesystem.h"

#if defined(MODIO_WINDOWS_DETECTED)
#include "WindowsFilesystem.h"
#include "utf8.h"

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
      std::wstring result;
      utf8::utf8to16(utf8_str.begin(),utf8_str.end(),std::back_inserter(result));
      return result;
    }

    std::string wstrToUtf8(const std::wstring& wide_string)
    {
	  std::string result;
	  utf8::utf16to8(wide_string.begin(), wide_string.end(), std::back_inserter(result));
	  return result;
    }
  }
}
#endif
