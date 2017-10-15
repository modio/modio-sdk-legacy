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
  void init(int game_id, string api_key);

  extern "C" MODIO_DLL void init(int game_id, const char* api_key, const char* root_path);
  MODIO_DLL void setDebugMode(DebugMode debug_mode);
  MODIO_DLL void shutdown();
  MODIO_DLL CurrentDownloadInfo getCurrentDownloadInfo();
  MODIO_DLL void pauseCurrentDownload();
}


#endif
