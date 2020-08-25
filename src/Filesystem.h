#ifndef MODIO_FILESYSTEM_H
#define MODIO_FILESYSTEM_H

#include "c/ModioC.h"
#include <string>

// @todonow: Move this when moving WideChar...
#include <codecvt>

namespace modio
{
  struct GenericFilesystem
  {
    static bool IsDir(const std::string& dir);
  };
}

#if defined(MODIO_WINDOWS_DETECTED)
namespace modio
{
  // @todonow: Migrate this to WindowsFilesystem.cpp
                               // for wstring_convert/codecvt_utf8
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
}
  #include "WindowsFilesystem.h"
#elif defined(MODIO_LINUX_DETECTED) || defined(MODIO_OSX_DETECTED)
  #include "UnixFilesystem.h"
#endif

#endif