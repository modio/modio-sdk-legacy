#include "c/methods/SettingsMethods.h"

extern "C"
{
  void modioInitConfig()
  {
    nlohmann::json config_json = modio::openJson(modio::getModIODirectory() + "config.json");

    if(!modio::hasKey(config_json, "automatic_updates"))
      config_json["automatic_updates"] = MODIO_UPDATES_ENABLED;

    if(!modio::hasKey(config_json, "allow_background_downloads"))
      config_json["allow_background_downloads"] = 1;

    modio::AUTOMATIC_UPDATES = config_json["automatic_updates"];
    modio::BACKGROUND_DOWNLOADS = config_json["allow_background_downloads"];
    modio::writeJson(modio::getModIODirectory() + "config.json", config_json);
  }

  u32 modioGetAutomaticUpdatesConfig()
  {
    nlohmann::json config_json = modio::openJson(modio::getModIODirectory() + "config.json");
    u32 automatic_updates = 0;
    if(modio::hasKey(config_json, "automatic_updates"))
      automatic_updates = config_json["automatic_updates"];
    return automatic_updates;
  }

  u32 modioGetAllowBackgroundDownloadsConfig()
  {
    nlohmann::json config_json = modio::openJson(modio::getModIODirectory() + "config.json");
    u32 allow_background_downloads = 0;
    if(modio::hasKey(config_json, "allow_background_downloads"))
      allow_background_downloads = config_json["allow_background_downloads"];
    return allow_background_downloads;
  }

  void modioSetAutomaticUpdatesConfig(u32 option)
  {
    nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "config.json");
    cache_file_json["automatic_updates"] = option;

    modio::AUTOMATIC_UPDATES = option;

    modio::writeJson(modio::getModIODirectory() + "config.json", cache_file_json);
  }

  void modioSetAllowBackgroundDownloadsConfig(u32 option)
  {
    nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "config.json");
    cache_file_json["allow_background_downloads"] = option;
    modio::writeJson(modio::getModIODirectory() + "config.json", cache_file_json);

    modio::BACKGROUND_DOWNLOADS = option;
  }
}
