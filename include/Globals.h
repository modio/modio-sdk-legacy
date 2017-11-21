#ifndef MODIO_GLOBALS_H
#define MODIO_GLOBALS_H

#include <iostream>
#include <thread>
#include "Utility.h"

typedef unsigned int u32;

namespace modio
{
  struct CurrentDownloadInfo
  {
    std::string url;
    long download_total;
    long download_progress;
  };

  extern std::string API_KEY;
  extern std::string ACCESS_TOKEN;
  extern int GAME_ID;
  extern std::string ROOT_PATH;
  extern unsigned int DEBUG_LEVEL;
  extern std::string MODIO_URL;
  extern std::string MODIO_VERSION_PATH;
}

#endif
