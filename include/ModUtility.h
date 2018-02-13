#ifndef MODIO_MODUTILITY_H
#define MODIO_MODUTILITY_H

#include "Utility.h"
#include "Globals.h"

namespace modio
{
  void addCallToCache(std::string url, json response_json);
  std::string getCallFileFromCache(std::string url, u32 max_age_seconds);
  void createInstalledModJson(json mod_id, std::string file_path);
  void addToInstalledModsJson(json mod_id, std::string path);
  bool checkIfModIsStillInstalled(std::string path, u32 modfile_id);
  void updateInstalledModsJson();
  std::string getInstalledModPath(u32 modfile_id);
}

#endif
