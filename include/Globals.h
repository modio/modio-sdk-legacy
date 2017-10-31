#ifndef MODIO_GLOBALS_H
#define MODIO_GLOBALS_H

#include <iostream>
#include <thread>
#include "Utility.h"

using namespace std;

namespace modio
{
  struct CurrentDownloadInfo
  {
    string url;
    long download_total;
    long download_progress;
  };

  extern string API_KEY;
  extern string ACCESS_TOKEN;
  extern int GAME_ID;
  extern string ROOT_PATH;
  extern unsigned int DEBUG_LEVEL;
  extern string MODIO_URL;
  extern string MODIO_VERSION_PATH;
}

#endif
