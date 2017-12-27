#ifndef MODIO_UTILITY_H
#define MODIO_UTILITY_H

#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>

#include "dependencies/json/json.hpp"
#include "Globals.h"

#ifdef __linux__
#define LINUX
#endif

#ifdef __APPLE__
#define OSX
#endif
#ifdef __MACH__
#define OSX
#endif

#ifdef _WIN32
#define WINDOWS
#endif
#ifdef _WIN64
#define WINDOWS
#endif

#ifdef WINDOWS
#  ifdef BUILDING_MODIO_DLL
#    define MODIO_DLL __declspec(dllexport)
#  else
#    define MODIO_DLL __declspec(dllimport)
#  endif
#else
#  define MODIO_DLL
#endif

#ifdef LINUX
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#include "dependencies/dirent/dirent.h"
#endif

#ifdef OSX
#include <sys/stat.h>
#include <dirent.h>
#endif

using json = nlohmann::json;

// NOTE(@jackson): Debug "Severity"? (Steamworks uses "spew level")
#define MODIO_DEBUGLEVEL_LOG      2
#define MODIO_DEBUGLEVEL_WARNING  1
#define MODIO_DEBUGLEVEL_ERROR    0

#define MODIO_MODFILE_NOT_INSTALLED 0
#define MODIO_MODFILE_INSTALLED     1
#define MODIO_MODFILE_INSTALLING    2

#ifndef PATH_MAX
#define PATH_MAX 260
#endif

namespace modio
{
  std::string toString(i32 number);
  std::string toString(u32 number);
  std::string toString(double number);
  void createDirectory(std::string directory);
  void clearLog();
  void writeLogLine(std::string text, unsigned int debug_level);
  std::vector<std::string> getFilenames(std::string directory);
  std::string getModIODirectory();
  bool hasKey(json json_object, std::string key);
  void removeFile(std::string filename);
  bool removeDirectory(std::string directory_name);
  std::string addSlashIfNeeded(std::string directory_path);
  bool checkIfModIsStillInstalled(std::string path, u32 modfile_id);
  void updateModfilesJson();
  std::string getModfilePath(u32 modfile_id);
}

#endif
