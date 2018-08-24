#include "ModUtility.h"

namespace modio
{
void addCallToCache(std::string url, nlohmann::json response_json)
{
  std::time_t datetime = std::time(nullptr);
  std::string filename = modio::toString((u32)datetime) + ".json";

  modio::writeJson(modio::getModIODirectory() + "cache/" + filename, response_json);

  nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache.json");

  for (nlohmann::json::iterator it = cache_file_json.begin(); it != cache_file_json.end(); ++it)
  {
    if ((*it)["url"] == url)
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

  while (cache_file_json.size() > modio::MAX_CALL_CACHE)
  {
    std::string filename = (*(cache_file_json.begin()))["file"];
    cache_file_json.erase(cache_file_json.begin());
    modio::removeFile(modio::getModIODirectory() + "cache/" + filename);
  }

  modio::writeJson(modio::getModIODirectory() + "cache.json", cache_file_json);
}

std::string getCallFileFromCache(std::string url, u32 max_age_seconds)
{
  nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache.json");
  for (nlohmann::json::iterator it = cache_file_json.begin(); it != cache_file_json.end(); ++it)
  {
    if ((*it)["url"] == url)
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

void addToInstalledModsJson(nlohmann::json mod_json, std::string path)
{
  nlohmann::json installed_mods_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");

  for (auto &installed_mod : installed_mods_json["mods"])
  {
    if (installed_mod["mod_id"] == mod_json["id"] && installed_mod["path"] == path)
    {
      return;
    }
  }

  nlohmann::json installed_mod_json;
  installed_mod_json["path"] = path;
  installed_mod_json["mod_id"] = mod_json["id"];
  installed_mod_json["modfile_id"] = mod_json["modfile"]["id"];
  installed_mod_json["updated_at"] = modio::getCurrentTime();

  installed_mods_json["mods"].push_back(installed_mod_json);

  modio::writeJson(modio::getModIODirectory() + "installed_mods.json", installed_mods_json);
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
  nlohmann::json resulting_json;
  nlohmann::json installed_mods_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");

  if (modio::hasKey(installed_mods_json, "mods"))
  {
    for (int i = 0; i < (int)installed_mods_json["mods"].size(); i++)
    {
      if (checkIfModIsStillInstalled(installed_mods_json["mods"][i]["path"], installed_mods_json["mods"][i]["mod_id"]))
      {
        resulting_json["mods"].push_back(installed_mods_json["mods"][i]);
      }
    }
  }

  if (modio::hasKey(installed_mods_json, "last_mod_event_poll"))
    resulting_json["last_mod_event_poll"] = installed_mods_json["last_mod_event_poll"];

  modio::writeJson(modio::getModIODirectory() + "installed_mods.json", resulting_json);
  modio::writeLogLine("Finished checking installed mod cache data...", MODIO_DEBUGLEVEL_LOG);
}

void clearOldCache()
{
  modio::writeLogLine("Clearing old cache files...", MODIO_DEBUGLEVEL_LOG);
  u32 current_time = modio::getCurrentTime();
  nlohmann::json cache_json = modio::openJson(modio::getModIODirectory() + "cache.json");
  nlohmann::json resulting_cache_json;
  for(auto cache_file_json : cache_json)
  {
    if(modio::hasKey(cache_file_json,"datetime"))
    {
      u32 cache_time = cache_file_json["datetime"];
      u32 time_difference = current_time - cache_time;

      if(time_difference > MAX_CALL_CACHE)
      {
        std::string cache_file_to_delete_path = modio::getModIODirectory() + "cache/";
        std::string cache_filename = cache_file_json["file"];
        cache_file_to_delete_path += cache_filename;
        modio::removeFile(cache_file_to_delete_path);
      }else
      {
        resulting_cache_json.push_back(cache_file_json);
      }
    }
  }
  modio::writeJson(modio::getModIODirectory() + "cache.json", resulting_cache_json);
  modio::writeLogLine("Finished clearing old cache files.", MODIO_DEBUGLEVEL_LOG);
}

std::string getAllInstalledModPath(u32 mod_id)
{
  nlohmann::json installed_mod_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");

  if (modio::hasKey(installed_mod_json, "mods"))
  {
    for (u32 i = 0; i < (u32)installed_mod_json["mods"].size(); i++)
    {
      if (mod_id == installed_mod_json["mods"][i]["mod_id"])
      {
        return installed_mod_json["mods"][i]["path"];
      }
    }
  }

  return "";
}

std::string getAllInstalledModfilePath(u32 modfile_id)
{
  nlohmann::json installed_mod_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");

  if (modio::hasKey(installed_mod_json, "mods"))
  {
    for (int i = 0; i < (int)installed_mod_json["mods"].size(); i++)
    {
      if (modfile_id == installed_mod_json["mods"][i]["mod"]["modfile"]["id"])
      {
        return installed_mod_json["mods"][i]["path"];
      }
    }
  }

  return "";
}
}
