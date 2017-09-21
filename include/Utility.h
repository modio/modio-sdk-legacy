#ifndef MODWORKS_UTILITY_H
#define MODWORKS_UTILITY_H

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
#include "dirent/dirent.h"
#endif

#ifdef OSX
#include <sys/stat.h>
#include <dirent.h>
#endif

#include <fstream>
#include "Globals.h"

using namespace std;

namespace modworks
{
  enum DebugMode : unsigned int { verbose, error };
  
  string dataToJsonString(char* data, size_t size);
  string dataToJsonString(string data);
  string toString(int number);
  void createDirectory(string directory);
  void clearLog();
  void writeLogLine(string text, DebugMode debug_mode);
  vector<string> getFilenames(string directory);
  string getModworksDirectory();
}

#endif
