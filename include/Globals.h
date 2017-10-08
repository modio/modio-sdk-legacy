#ifndef MODIO_GLOBALS_H
#define MODIO_GLOBALS_H

#include <iostream>
using namespace std;

#ifdef WINDOWS
#  ifdef BUILDING_MODIO_DLL
#    define MODIO_DLL __declspec(dllexport)
#  else
#    define MODIO_DLL __declspec(dllimport)
#  endif
#else
#  define MODIO_DLL
#endif

#include "Utility.h"

namespace modio
{
  struct CurrentDownloadInfo
  {
    string url;
    long download_total;
    long download_progress;
  };

  enum DebugMode : unsigned int;

  extern string api_key;
  extern string access_token;
  extern int game_id;
  extern string ROOT_PATH;
  extern DebugMode DEBUG_LEVEL;
}

#endif
