#include "ModUtility.h"

namespace modio
{
void addCallToCache(std::string url, json response_json)
{
  std::time_t datetime = std::time(nullptr);
  std::string filename = modio::toString((u32)datetime) + ".json";
  std::ofstream o(modio::getModIODirectory() + "cache/" + filename);
  o << std::setw(4) << response_json << std::endl;

  json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache.json");

  for (json::iterator it = cache_file_json.begin(); it != cache_file_json.end(); ++it)
  {
    if ((*it)["url"] == url)
    {
      std::string filename = (*it)["file"];
      cache_file_json.erase(it);
      modio::removeFile(modio::getModIODirectory() + "cache/" + filename);
      break;
    }
  }

  json cache_object;
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
  json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache.json");
  for (json::iterator it = cache_file_json.begin(); it != cache_file_json.end(); ++it)
  {
    if ((*it)["url"] == url)
    {
      u32 current_datetime = (u32)std::time(nullptr);
      u32 file_datetime = (*it)["datetime"];
      u32 difference = current_datetime - file_datetime;

      if (difference <= max_age_seconds)
      {
        return (*it)["file"];
      }
    }
  }
  return "";
}

void createInstalledModJson(json mod_json, std::string file_path)
{
  std::ofstream out(file_path.c_str());
  out << std::setw(4) << mod_json << std::endl;
  out.close();
}

void addToInstalledModsJson(json mod_json, std::string path)
{
  json installed_mods_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");

  for (auto &installed_mod : installed_mods_json["mods"])
  {
    if (installed_mod["mod_id"] == mod_json["id"] && installed_mod["path"] == path)
    {
      return;
    }
  }

  json installed_mod_json;
  installed_mod_json["path"] = path;
  installed_mod_json["mod_id"] = mod_json["id"];
  installed_mod_json["modfile_id"] = mod_json["modfile"]["id"];
  installed_mod_json["updated_at"] = modio::getCurrentTime();

  installed_mods_json["mods"].push_back(installed_mod_json);

  modio::writeJson(modio::getModIODirectory() + "installed_mods.json", installed_mods_json);
}

bool checkIfModIsStillInstalled(std::string path, u32 mod_id)
{
  json installed_mod_json = modio::openJson(path + "modio.json");
  if (modio::hasKey(installed_mod_json, "id"))
    return mod_id == installed_mod_json["id"];
  return false;
}

bool checkIfModfileIsStillInstalled(std::string path, u32 modfile_id)
{
  json installed_mod_json = modio::openJson(path + "modio.json");
  if (modio::hasKey(installed_mod_json, "modfile") && modio::hasKey(installed_mod_json["modfile"], "id"))
    return modfile_id == installed_mod_json["modfile"]["id"];
  return false;
}

void updateInstalledModsJson()
{
  json resulting_json;
  json installed_mods_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");

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

  if (modio::hasKey(installed_mods_json, "last_user_event_poll"))
    resulting_json["last_user_event_poll"] = installed_mods_json["last_user_event_poll"];
  if (modio::hasKey(installed_mods_json, "last_mod_event_poll"))
    resulting_json["last_mod_event_poll"] = installed_mods_json["last_mod_event_poll"];

  modio::writeJson(modio::getModIODirectory() + "installed_mods.json", resulting_json);
}

void checkForInstalledModsUpdates()
{
  ModioFilterCreator filter;
  modioInitFilter(&filter);
  u32 installed_mods_size = modioGetInstalledModsSize();
  ModioInstalledMod *modio_installed_mods = new ModioInstalledMod[installed_mods_size];
  modioGetInstalledMods(modio_installed_mods);

  for (u32 i = 0; i < (u32)installed_mods_size; i++)
  {
    modioAddFilterInField(&filter, "id", (char *)modio::toString(modio_installed_mods[i].mod_id).c_str());
  }
  modioGetMods(NULL, filter, &onGetInstalledMods);

  delete[] modio_installed_mods;
}

std::string getInstalledModPath(u32 mod_id)
{
  json installed_mod_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");

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

std::string getInstalledModfilePath(u32 modfile_id)
{
  json installed_mod_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");

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
