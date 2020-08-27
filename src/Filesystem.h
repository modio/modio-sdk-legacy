#ifndef MODIO_FILESYSTEM_H
#define MODIO_FILESYSTEM_H

#include "c/ModioC.h"
#include <string>

#if defined(MODIO_WINDOWS_DETECTED)
#include <codecvt>
namespace modio
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
}
#endif

#endif