#include "Filesystem.h"
#include <iostream>

namespace modio
{
  bool GenericFilesystem::IsDir(const ::std::string& dir)
  {
    return Filesystem::DirExists(dir);
  }

  std::string GenericFilesystem::StripTrailingSlash(const std::string& path)
  {
    std::string result = path;
    if(result.length() > 0 )
    {
      const char& lastChar = result[result.length() -1];
      if( lastChar == '/' || lastChar == '\\' )
      {
        result.pop_back();
      }
    }

    return result;
  }
}