#include "ModUtility.h"

namespace modio
{
void addCallToCache(std::string url, nlohmann::json response_json)
{
  double current_time_millis = modio::getCurrentTimeMillis();
  std::string current_time_string = modio::toString(current_time_millis);
  current_time_string.erase(current_time_string.find('.'), std::string::npos);
  std::string filename = current_time_string + ".json";

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
  cache_object["datetime"] = current_time_millis;
  cache_object["file"] = filename;
  cache_object["url"] = url;
  cache_file_json.push_back(cache_object);

  modio::writeJson(modio::getModIODirectory() + "cache.json", cache_file_json);
}

std::string getCallFileFromCache(std::string url, u32 max_age_seconds)
{
  nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache.json");
  double current_time = modio::getCurrentTimeMillis();
  for (nlohmann::json::iterator it = cache_file_json.begin(); it != cache_file_json.end(); ++it)
  {
    if (modio::hasKey((*it), "url") && modio::hasKey((*it), "datetime") && modio::hasKey((*it), "file") && (*it)["url"] == url)
    {
      double file_datetime = (*it)["datetime"];
      double difference = current_time - file_datetime;

      if (difference <= max_age_seconds * 1000)
      {
        return (*it)["file"];
      }
    }
  }
  return "";
}

void installDownloadedMods()
{
  modio::writeLogLine("Installing downloaded mods...", MODIO_DEBUGLEVEL_LOG);

  nlohmann::json downloaded_mods = modio::openJson(modio::getModIODirectory() + "downloaded_mods.json");

  for (auto &downloaded_mod : downloaded_mods)
  {
    std::string installation_path = downloaded_mod["installation_path"];
    std::string downloaded_zip_path = downloaded_mod["downloaded_zip_path"];
    nlohmann::json mod_json = downloaded_mod["mod"];

    if (modio::hasKey(mod_json, "id") &&
        modio::hasKey(mod_json, "modfile") &&
        modio::hasKey(mod_json["modfile"], "id") &&
        modio::hasKey(mod_json, "date_updated"))
    {
      u32 mod_id = mod_json["id"];
      u32 modfile_id = mod_json["modfile"]["id"];
      u32 date_updated = mod_json["date_updated"];

      modio::writeLogLine("Installing mod " + modio::toString(mod_id), MODIO_DEBUGLEVEL_LOG);

      modio::createDirectory(installation_path);
      modio::writeLogLine("Extracting...", MODIO_DEBUGLEVEL_LOG);
      modio::minizipwrapper::extract(downloaded_zip_path, installation_path);
      modio::writeLogLine("Removing temporary file...", MODIO_DEBUGLEVEL_LOG);
      modio::removeFile(downloaded_zip_path);
      modio::writeJson(installation_path + std::string("modio.json"), mod_json);

      modio::addToInstalledModsJson(mod_id,
                                    installation_path,
                                    modfile_id,
                                    date_updated);

      modio::writeLogLine("Finished installing mod", MODIO_DEBUGLEVEL_LOG);
    }
    else
    {
      modio::writeLogLine("Mod data is missing, could not install mod.", MODIO_DEBUGLEVEL_ERROR);
    }
  }
  nlohmann::json empty_json;
  modio::writeJson(modio::getModIODirectory() + "downloaded_mods.json", empty_json);
  modio::writeLogLine("Finished installing downloaded mods", MODIO_DEBUGLEVEL_LOG);
}

nlohmann::json createInstalledModJson(std::string installation_path, std::string downloaded_zip_path, nlohmann::json mod_json)
{
  nlohmann::json downloaded_mod;
  downloaded_mod["installation_path"] = installation_path;
  downloaded_mod["downloaded_zip_path"] = downloaded_zip_path;
  downloaded_mod["mod"] = mod_json;
  return downloaded_mod;
}

void addToDownloadedModsJson(std::string installation_path, std::string downloaded_zip_path, nlohmann::json mod_json)
{
  nlohmann::json downloaded_mods = modio::openJson(modio::getModIODirectory() + "downloaded_mods.json");

  bool already_downloaded = false;

  for (auto &downloaded_mod : downloaded_mods)
  {
    if (modio::hasKey(downloaded_mod, "mod") &&
        modio::hasKey(downloaded_mod["mod"], "id") &&
        downloaded_mod["mod"]["id"] == mod_json["id"])
    {
      already_downloaded = true;
      downloaded_mod = createInstalledModJson(installation_path, downloaded_zip_path, mod_json);
    }
  }

  if (!already_downloaded)
    downloaded_mods.push_back(createInstalledModJson(installation_path, downloaded_zip_path, mod_json));

  modio::writeJson(modio::getModIODirectory() + "downloaded_mods.json", downloaded_mods);
}

void addToInstalledModsJson(u32 mod_id, std::string path, u32 modfile_id, u32 date_updated)
{
  bool mod_reinstalled = false;
  for (auto &installed_mod : modio::installed_mods)
  {
    if (modio::hasKey(installed_mod, "mod_id") &&
        modio::hasKey(installed_mod, "path") &&
        installed_mod["mod_id"] == mod_id &&
        installed_mod["path"] == path)
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
    if (modio::hasKey(stored_installed_mod, "path") && modio::hasKey(stored_installed_mod, "mod_id") && checkIfModIsStillInstalled(stored_installed_mod["path"], stored_installed_mod["mod_id"]))
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
    if (modio::hasKey(cache_file_json, "datetime") && modio::hasKey(cache_file_json, "file"))
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
    if (modio::hasKey(installed_mod_json, "mod_id") && modio::hasKey(installed_mod_json, "path") && installed_mod_json["mod_id"] == mod_id)
    {
      return installed_mod_json["path"];
    }
  }
  return "";
}
} // namespace modio
