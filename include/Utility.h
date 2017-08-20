#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

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
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

using namespace std;

string dataToJsonString(char* data, size_t size);
string toString(int number);
void createDirectory(string directory);

#endif
