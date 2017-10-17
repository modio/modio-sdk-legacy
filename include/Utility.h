#ifndef MODIO_UTILITY_H
#define MODIO_UTILITY_H

#include <iostream>
#include <vector>
#include <string.h>

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

#ifdef LINUX
#include <sys/stat.h>
#include <dirent.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#include "dependencies/dirent/dirent.h"
#endif

#ifdef OSX
#include <sys/stat.h>
#include <dirent.h>
#endif

#include <fstream>
#include "dependencies/json/json.hpp"
#include "Globals.h"

using namespace std;
using json = nlohmann::json;

// NOTE(@jackson): Debug "Severity"? (Steamworks uses "spew level")
#define MODIO_DEBUGLEVEL_LOG      2
#define MODIO_DEBUGLEVEL_WARNING  1
#define MODIO_DEBUGLEVEL_ERROR    0

namespace modio
{
  string dataToJsonString(char* data, size_t size);
  string dataToJsonString(string data);
  string toString(int number);
  void createDirectory(string directory);
  void clearLog();
  void writeLogLine(string text, unsigned int debug_level);
  vector<string> getFilenames(string directory);
  string getModIODirectory();
  bool hasKey(json json_object, string key);
  void removeFile(string filename);
}

#endif
