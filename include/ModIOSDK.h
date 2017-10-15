#ifndef MODIO_SDK_H
#define MODIO_SDK_H

//#pragma warning(disable : 4503)

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Mod.h"
#include "Globals.h"
#include "exported_methods/AuthenticationMethods.h"
#include "exported_methods/ModMethods.h"
#include "exported_methods/ModfileMethods.h"
#include "exported_methods/TagMethods.h"

namespace modio
{
  MODIO_DLL void init(int game_id, string api_key);
  MODIO_DLL CurrentDownloadInfo getCurrentDownloadInfo();

  extern "C" MODIO_DLL void init(int game_id, const char* api_key, const char* root_path);
  extern "C" MODIO_DLL void setDebugLevel(unsigned int debug_level);
  extern "C" MODIO_DLL void shutdown();
  extern "C" MODIO_DLL void pauseCurrentDownload();
}


#endif
