#ifndef MODIO_QUEUEDMODDOWNLOAD_H
#define MODIO_QUEUEDMODDOWNLOAD_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "c/ModioC.h"

using json = nlohmann::json;

extern "C"
{
  void modioInitQueuedModDownload(ModioQueuedModDownload* queued_mod_download, json queued_mod_download_json);
  void modioFreeQueuedModDownload(ModioQueuedModDownload* queued_mod_download);
}

#endif
