#ifndef MODIO_SDK_H
#define MODIO_SDK_H

//#pragma warning(disable : 4503)

#include "wrappers/CurlWrapper.h"
#include "wrappers/MinizipWrapper.h"
#include "data_containers/Mod.h"
#include "Globals.h"
#include "AuthenticationMethods.h"
#include "ModMethods.h"
#include "ModfileMethods.h"

namespace modio
{
  MODIO_DLL void init(int game_id, string api_key);
  MODIO_DLL void init(int game_id, string api_key, string root_path);
  MODIO_DLL void setDebugMode(DebugMode debug_mode);
  MODIO_DLL void shutdown();
  MODIO_DLL CurrentDownloadInfo getCurrentDownloadInfo();
  MODIO_DLL void pauseCurrentDownload();
}


#endif
