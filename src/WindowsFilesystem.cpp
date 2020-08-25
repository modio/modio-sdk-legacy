#include "Filesystem.h"
#include <iostream>
#include "Utility.h"

#if defined(MODIO_WINDOWS_DETECTED)
#include <windows.h>

namespace modio
{
  static void writeLastErrorLog(const std::string& error_function, DWORD inErrorMessageId = -1);

  bool WindowsFilesystem::DirExists(const std::string& directory)
  {
    DWORD attributes = ::GetFileAttributes(WideCharFromString(directory).c_str());
    if (attributes == INVALID_FILE_ATTRIBUTES)
    {
      return false;
    }

    if (attributes & FILE_ATTRIBUTE_DIRECTORY)
    {
      return true;
    }

    return false;
  }

  bool WindowsFilesystem::CreateDir(const std::string& directory)
  {
    // Trying to Create a directory that is directly a drive won't return ERROR_ALREADY_EXISTS, but a 
    // ERROR_ACCESS_DENIED error that is a valid error
    if (WindowsFilesystem::IsDrive(directory))
    {
      return true;
    }

    std::wstring directoryWide = WideCharFromString(directory);

    if (!::CreateDirectory(directoryWide.c_str(), NULL))
    {
      DWORD errorId = ::GetLastError();
      // ERROR_ALREADY_EXISTS is returned if a FILE or folder exists, that's ok if that happens, as long as it's a folder
      if (!(errorId == ERROR_ALREADY_EXISTS && Filesystem::DirExists(directory)))
      {
        std::cerr << "[mod.io] Error: Could not create directory: " << directory << std::endl;
        modio::writeLastErrorLog("CreateDirectory", errorId);
        return false;
      }
    }

    return true;
  }

  bool WindowsFilesystem::IsDrive(const std::string& path)
  {
    if (path.length() == 3)
    {
      if (path[1] == ':' && path[2] == '/')
      {
        return true;
      }
    }
    return false;
  }


  void writeLastErrorLog(const std::string& error_function, DWORD inErrorMessageId /**= -1*/)
  {
    std::cerr << "[mod.io] Could not create directory on operating system Windows" << std::endl;
    //Get the error message, if any.
    DWORD errorMessageID = inErrorMessageId == -1 ? ::GetLastError() : inErrorMessageId;
    if (errorMessageID == 0)
    {
      std::cerr << "[mod.io] Error: No error message has been recorded" << std::endl;
      return; //No error message has been recorded
    }

    if (errorMessageID == ERROR_ALREADY_EXISTS)
    {
      std::cerr << "[mod.io] Error: The directory already exists" << std::endl;
      modio::writeLogLine("The directory already exists.", MODIO_DEBUGLEVEL_LOG);
      return;
    }

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    std::string message(messageBuffer, size);

    modio::writeLogLine("Error while using " + error_function + ": " + message, MODIO_DEBUGLEVEL_ERROR);
    std::cerr << "[mod.io] Error: while using " + error_function + ": " + message << " id " << errorMessageID << std::endl;

    //Free the buffer.
    LocalFree(messageBuffer);
  }
}

#endif