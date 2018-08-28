#ifndef MODIO_MODUTILITY_H
#define MODIO_MODUTILITY_H

#include "Utility.h"
#include "Globals.h"

namespace modio
{
  void addCallToCache(std::string url, nlohmann::json response_json);
  std::string getCallFileFromCache(std::string url, u32 max_age_seconds);
  void addToInstalledModsJson(nlohmann::json mod_id, std::string path);
  bool checkIfModIsStillInstalled(std::string path, u32 mod_id);
  bool checkIfModfileIsStillInstalled(std::string path, u32 modfile_id);
  void updateInstalledModsJson();
  void clearOldCache();
  std::string getAllInstalledModfilePath(u32 modfile_id);
  std::string getAllInstalledModPath(u32 mod_id);
  void updateModsCache(std::vector<u32> mod_ids);
}

#endif
