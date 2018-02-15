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
      if((*it)["url"] == url)
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

    while(cache_file_json.size() > modio::MAX_CALL_CACHE)
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
      if((*it)["url"] == url)
      {
        u32 current_datetime = (u32)std::time(nullptr);
        u32 file_datetime = (*it)["datetime"];
        u32 difference = current_datetime - file_datetime;

        if(difference <= max_age_seconds)
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
    out<<std::setw(4)<<mod_json<<std::endl;
    out.close();
  }

  void addToInstalledModsJson(json mod_json, std::string path)
  {
    json installed_mods_json;
    std::ifstream ifs(modio::getModIODirectory() + "installed_mods.json");
    if(ifs.is_open())
    {
      ifs >> installed_mods_json;
      ifs.close();
      for (auto& it : installed_mods_json["mods"])
      {
        if(it["id"] == mod_json["id"] && it["path"] == path)
        {
          return;
        }
      }
    }

    json installed_mod_json;
    installed_mod_json["path"] = path;
    installed_mod_json["mod_id"] = mod_json["id"];
    installed_mod_json["modfile_id"] = mod_json["modfile"]["id"];
    installed_mod_json["updated_at"] = modio::getCurrentTime();

    installed_mods_json["mods"].push_back(installed_mod_json);
    std::ofstream ofs(modio::getModIODirectory() + "installed_mods.json");
    ofs<<std::setw(4)<<installed_mods_json<<std::endl;
    ofs.close();
  }

  bool checkIfModIsStillInstalled(std::string path, u32 modfile_id)
  {
    std::string installed_mod_json_path = path + "modio.json";
    std::ifstream installed_mod_file(installed_mod_json_path.c_str());
    if(!installed_mod_file.is_open())
    {
      return false;
    }
    json installed_mod_json;
    installed_mod_file >> installed_mod_json;
    return modfile_id == installed_mod_json["modfile"]["id"];
  }

  void updateInstalledModsJson()
  {
    std::ifstream installed_mods_file(modio::getModIODirectory() + "installed_mods.json");
    if(installed_mods_file.is_open())
    {
      json installed_mods_json;
      json resulting_json;
      installed_mods_file >> installed_mods_json;
      installed_mods_file.close();

      for(int i=0; i<(int)installed_mods_json["mods"].size(); i++)
      {
        if(checkIfModIsStillInstalled(installed_mods_json["mods"][i]["path"], installed_mods_json["mods"][i]["modfile_id"]))
        {
          resulting_json["mods"].push_back(installed_mods_json["mods"][i]);
        }
      }
      std::ofstream out(modio::getModIODirectory() + "installed_mods.json");
      out<<std::setw(4)<<resulting_json<<std::endl;
      out.close();
    }
  }

  std::string getInstalledModPath(u32 modfile_id)
  {
    std::ifstream installed_mod_file(modio::getModIODirectory() + "installed_mods.json");
    if(installed_mod_file.is_open())
    {
      json installed_mod_json;
      try
      {
        installed_mod_file >> installed_mod_json;
        installed_mod_file.close();
        for(int i=0; i<(int)installed_mod_json["mods"].size(); i++)
        {
          if(modfile_id == installed_mod_json["mods"][i]["mod"]["modfile"]["id"])
          {
            return installed_mod_json["mods"][i]["path"];
          }
        }
      }catch(json::parse_error &e)
      {
        modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
      }
    }
    return "";
  }
}
