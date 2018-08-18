#ifndef MODIO_UTILITY_H
#define MODIO_UTILITY_H

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
#ifdef BUILDING_MODIO_DLL
#define MODIO_DLL __declspec(dllexport)
#else
#define MODIO_DLL __declspec(dllimport)
#endif
#else
#define MODIO_DLL
#endif

#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>

#include "c/ModioC.h"
#include "dependencies/json/json.hpp"
#include "Globals.h"

#ifdef LINUX
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#include <strsafe.h>
#include "dependencies/dirent/dirent.h"
#endif

#ifdef OSX
#include <sys/stat.h>
#include <dirent.h>
#endif

#ifndef PATH_MAX
#define PATH_MAX 260
#endif

namespace modio
{
// String methods
std::string MODIO_DLL toString(i32 number);
std::string MODIO_DLL toString(u32 number);
std::string MODIO_DLL toString(double number);
std::string replaceSubstrings(std::string str, const std::string &from, const std::string &to);
std::string addSlashIfNeeded(std::string directory_path);

// Log methods
void writeLogLine(std::string text, u32 debug_level);
void clearLog();

// Time methods
u32 getCurrentTime();

// Json methods
bool hasKey(nlohmann::json json_object, std::string key);
nlohmann::json toJson(std::string json_str);
nlohmann::json openJson(std::string file_path);
void writeJson(std::string file_path, nlohmann::json json_object);

// Filesystem methods
std::string getModIODirectory();
std::vector<std::string> getFilenames(std::string directory);
void createDirectory(std::string directory);
bool removeDirectory(std::string directory_name);
void removeFile(std::string filename);
double getFileSize(std::string file_path);
void createPath(std::string strPathAndFile);
}

#endif
