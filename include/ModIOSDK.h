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
  void MODIO_DLL init(int game_id, string api_key);
  void MODIO_DLL init(int game_id, string api_key, string root_path);
  void MODIO_DLL setDebugMode(DebugMode debug_mode);
  void MODIO_DLL shutdown();
  CurrentDownloadInfo MODIO_DLL getCurrentDownloadInfo();
  void MODIO_DLL pauseCurrentDownload();
}

#endif
