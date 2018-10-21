#include "ModUtility.h"

namespace modio
{
void addCallToCache(std::string url, nlohmann::json response_json)
{
  std::time_t datetime = std::time(nullptr);
  std::string filename = modio::toString((u32)datetime) + ".json";

  modio::writeJson(modio::getModIODirectory() + "cache/" + filename, response_json);

  nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache.json");

  // TODO: Restore automatic cache removal?
  for (nlohmann::json::iterator it = cache_file_json.begin(); it != cache_file_json.end(); ++it)
  {
    if (modio::hasKey((*it), "url") && modio::hasKey((*it), "file") && (*it)["url"] == url)
    {
      std::string filename = (*it)["file"];
      cache_file_json.erase(it);
      modio::removeFile(modio::getModIODirectory() + "cache/" + filename);
      break;
    }
  }

  nlohmann::json cache_object;
  cache_object["datetime"] = datetime;
  cache_object["file"] = filename;
  cache_object["url"] = url;
  cache_file_json.push_back(cache_object);

  modio::writeJson(modio::getModIODirectory() + "cache.json", cache_file_json);
}

std::string getCallFileFromCache(std::string url, u32 max_age_seconds)
{
  nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache.json");
  for (nlohmann::json::iterator it = cache_file_json.begin(); it != cache_file_json.end(); ++it)
  {
    if (modio::hasKey((*it), "url") && modio::hasKey((*it), "datetime") && modio::hasKey((*it), "file") && (*it)["url"] == url)
    {
      u32 current_time = modio::getCurrentTime();
      u32 file_datetime = (*it)["datetime"];
      u32 difference = current_time - file_datetime;

      if (difference <= max_age_seconds)
      {
        return (*it)["file"];
      }
    }
  }
  return "";
}

void addToInstalledModsJson(u32 mod_id, std::string path, u32 modfile_id, u32 date_updated)
{
  bool mod_reinstalled = false;
  for (auto &installed_mod : modio::installed_mods)
  {
    if (modio::hasKey(installed_mods, "mod_id") && modio::hasKey(installed_mods, "path") && installed_mod["mod_id"] == mod_id && installed_mod["path"] == path)
    {
      installed_mod["modfile_id"] = modfile_id;
      installed_mod["date_updated"] = date_updated;
      mod_reinstalled = true;
      break;
    }
  }

  if (!mod_reinstalled)
  {
    nlohmann::json installed_mod_json;
    installed_mod_json["path"] = path;
    installed_mod_json["mod_id"] = mod_id;
    installed_mod_json["modfile_id"] = modfile_id;
    installed_mod_json["date_updated"] = date_updated;

    modio::installed_mods.push_back(installed_mod_json);
  }

  modio::writeJson(modio::getModIODirectory() + "installed_mods.json", modio::installed_mods);
}

bool checkIfModIsStillInstalled(std::string path, u32 mod_id)
{
  nlohmann::json installed_mod_json = modio::openJson(path + "modio.json");
  if (modio::hasKey(installed_mod_json, "id"))
    return mod_id == installed_mod_json["id"];
  return false;
}

bool checkIfModfileIsStillInstalled(std::string path, u32 modfile_id)
{
  nlohmann::json installed_mod_json = modio::openJson(path + "modio.json");
  if (modio::hasKey(installed_mod_json, "modfile") && modio::hasKey(installed_mod_json["modfile"], "id"))
    return modfile_id == installed_mod_json["modfile"]["id"];
  return false;
}

void updateInstalledModsJson()
{
  modio::writeLogLine("Checking installed mod cache data...", MODIO_DEBUGLEVEL_LOG);
  nlohmann::json stored_installed_mods = modio::openJson(modio::getModIODirectory() + "installed_mods.json");
  modio::installed_mods.clear();

  // Migrating from v0.9.0
  if (modio::hasKey(stored_installed_mods, "mods"))
  {
    stored_installed_mods = stored_installed_mods["mods"];
  }

  for (auto stored_installed_mod : stored_installed_mods)
  {
    if (modio::hasKey(stored_installed_mod, "path")
        && modio::hasKey(stored_installed_mod, "mod_id")
        && checkIfModIsStillInstalled(stored_installed_mod["path"], stored_installed_mod["mod_id"]))
    {
      modio::installed_mods.push_back(stored_installed_mod);
    }
  }

  modio::writeJson(modio::getModIODirectory() + "installed_mods.json", modio::installed_mods);
  modio::writeLogLine("Finished checking installed mod cache data...", MODIO_DEBUGLEVEL_LOG);
}

void clearOldCache()
{
  modio::writeLogLine("Clearing old cache files...", MODIO_DEBUGLEVEL_LOG);
  u32 current_time = modio::getCurrentTime();
  nlohmann::json cache_json = modio::openJson(modio::getModIODirectory() + "cache.json");
  nlohmann::json resulting_cache_json;
  for (auto cache_file_json : cache_json)
  {
    if (modio::hasKey(cache_file_json, "datetime")
        && modio::hasKey(cache_file_json, "file"))
    {
      u32 cache_time = cache_file_json["datetime"];
      u32 time_difference = current_time - cache_time;

      if (time_difference > MAX_CACHE_TIME)
      {
        std::string cache_file_to_delete_path = modio::getModIODirectory() + "cache/";
        std::string cache_filename = cache_file_json["file"];
        cache_file_to_delete_path += cache_filename;
        modio::removeFile(cache_file_to_delete_path);
      }
      else
      {
        resulting_cache_json.push_back(cache_file_json);
      }
    }
  }
  modio::writeJson(modio::getModIODirectory() + "cache.json", resulting_cache_json);
  modio::writeLogLine("Finished clearing old cache files.", MODIO_DEBUGLEVEL_LOG);
}

std::string getInstalledModPath(u32 mod_id)
{
  for (auto installed_mod_json : modio::installed_mods)
  {
    if (modio::hasKey(installed_mod_json, "mod_id")
        && modio::hasKey(installed_mod_json, "path")
        && installed_mod_json["mod_id"] == mod_id)
    {
      return installed_mod_json["path"];
    }
  }
  return "";
}
} // namespace modio
