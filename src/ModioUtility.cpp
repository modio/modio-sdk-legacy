#include "ModioUtility.h"

namespace modio
{
void updateModCache(u32 mod_id)
{
  std::string mod_path_str = modio::getInstalledModPath(mod_id);
  char *mod_path = new char[mod_path_str.size() + 1];
  strcpy(mod_path, mod_path_str.c_str());
  modioGetMod(mod_path, mod_id, &modio::onModUpdateEvent);
}

void onGetInstalledMods(void *object, ModioResponse response, ModioMod *mods, u32 mods_size)
{
  if (response.code == 200)
  {
    u32 installed_mods_size = modioGetInstalledModsCount();
    ModioInstalledMod *modio_installed_mods = new ModioInstalledMod[installed_mods_size];
    modioGetInstalledMods(modio_installed_mods);
    for (u32 i = 0; i < mods_size; i++)
    {
      for (u32 j = 0; j < (u32)installed_mods_size; j++)
      {
        if (mods[i].id == modio_installed_mods[j].mod.id)
        {
          if (mods[i].modfile.date_added != modio_installed_mods[j].mod.modfile.date_added)
          {
            modioInstallMod(mods[i].id);
          }
          else if (mods[i].date_updated != modio_installed_mods[j].mod.date_updated)
          {
            modio::updateModCache(mods[i].id);
          }
        }
      }
    }
    delete[] modio_installed_mods;
  }
}

void onModUpdateEvent(void *object, ModioResponse response, ModioMod modio_mod)
{
  modio::writeLogLine("Mod updated", MODIO_DEBUGLEVEL_LOG);
  char *mod_path = (char *)object;
  std::string mod_path_str = std::string(mod_path) + "modio.json";
  if (response.code == 200)
  {
    modio::Mod mod;
    mod.initialize(modio_mod);
    modio::writeJson(mod_path_str, mod.toJson());
  }
  if (mod_path)
    delete[] mod_path;
}

void onGetAllEventsPoll(void *object, ModioResponse response, ModioEvent *events_array, u32 events_array_size)
{
  if (response.code == 200)
  {
    writeLogLine("Mod events polled", MODIO_DEBUGLEVEL_LOG);
    if (modio::callback)
      modio::callback(response, events_array, events_array_size);

    for (int i = 0; i < (int)events_array_size; i++)
    {
      switch (events_array[i].event_type)
      {
      case MODIO_EVENT_UNDEFINED:
        // TODO: Log error
        break;
      case MODIO_EVENT_MODFILE_CHANGED:
      {
        bool reinstall = true;
        ModioInstalledMod installed_mod;
        if(modioGetInstalledModById(events_array[i].mod_id, &installed_mod))
        {
          if(installed_mod.mod.modfile.date_added >= events_array[i].date_added)
          {
            reinstall = false;
            writeLogLine("Modfile changed event detected but you already have a newer version installed, the modfile will not be downloaded. Mod id: " + modio::toString(events_array[i].mod_id), MODIO_DEBUGLEVEL_LOG);
          }
        }
        if(reinstall)
        {
          writeLogLine("Modfile changed. Mod id: " + modio::toString(events_array[i].mod_id) + " Reisntalling...", MODIO_DEBUGLEVEL_LOG);
          modioInstallMod(events_array[i].mod_id);
        }
      }
      break;
      case MODIO_EVENT_MOD_AVAILABLE:
      {
        // N/A
        break;
      }
      case MODIO_EVENT_MOD_UNAVAILABLE:
      {
        // N/A
        break;
      }
      case MODIO_EVENT_MOD_EDITED:
      {
        writeLogLine("Mod updated. Mod id: " + modio::toString(events_array[i].mod_id) + " Updating cache...", MODIO_DEBUGLEVEL_LOG);
        updateModCache(events_array[i].mod_id);
        break;
      }
      }
    }
    json installed_mods_json = modio::openJson(modio::getModIODirectory() + "installed_mods.json");
    installed_mods_json["last_mod_event_poll"] = modio::LAST_MOD_EVENT_POLL;
    modio::writeJson(modio::getModIODirectory() + "installed_mods.json", installed_mods_json);
  }
  else
  {
    writeLogLine("Could not poll mod events. Error code: " + modio::toString(response.code), MODIO_DEBUGLEVEL_ERROR);
  }
}

void onGetUserEventsPoll(void *object, ModioResponse response, ModioEvent *events_array, u32 events_array_size)
{
  if (response.code == 200)
  {
    //TODO: Register User Callback
    if(modio::callback)
      modio::callback(response, events_array, events_array_size);
    writeLogLine("User events polled ", MODIO_DEBUGLEVEL_LOG);

    for (int i = 0; i < (int)events_array_size; i++)
    {
      switch (events_array[i].event_type)
      {
      case MODIO_EVENT_UNDEFINED:
        // TODO: Log error
        break;
      case MODIO_EVENT_USER_TEAM_JOIN:
      {
        // TODO: N/A
      }
      break;
      case MODIO_EVENT_USER_TEAM_LEAVE:
      {
        // N/A
        break;
      }
      case MODIO_EVENT_USER_SUBSCRIBE:
      {
        writeLogLine("Current User subscribed to a Mod. Mod id: " + modio::toString(events_array[i].mod_id) + " Installing...", MODIO_DEBUGLEVEL_LOG);
        std::string modfile_path_str = modio::getInstalledModPath(events_array[i].mod_id);
        if (modfile_path_str == "")
        {
          writeLogLine("Installing mod. Id: " + modio::toString(events_array[i].mod_id), MODIO_DEBUGLEVEL_LOG);
          modioInstallMod(events_array[i].mod_id);
        }
        break;
      }
      case MODIO_EVENT_USER_UNSUBSCRIBE:
      {
        // TODO: N/A
        writeLogLine("Current User unsubscribed from a Mod. Mod id: " + modio::toString(events_array[i].mod_id) + " Uninstalling...", MODIO_DEBUGLEVEL_LOG);
        modioUninstallMod(events_array[i].mod_id);
        break;
      }
      }
    }
    json token_json = modio::openJson(modio::getModIODirectory() + "authentication.json");
    token_json["last_user_event_poll"] = modio::LAST_USER_EVENT_POLL;
    modio::writeJson(modio::getModIODirectory() + "authentication.json", token_json);
  }
  else
  {
    writeLogLine("Could not poll user events. Error code: " + modio::toString(response.code), MODIO_DEBUGLEVEL_ERROR);
  }
}

void pollEvents()
{
  u32 current_time = modio::getCurrentTime();

  if(current_time < modio::RETRY_AFTER)
  {
    modio::writeLogLine("API request limit hit. Could not poll events. Rerying after " + modio::toString(RETRY_AFTER), MODIO_DEBUGLEVEL_WARNING);
  }
  else
  {
    if (modioGetInstalledModsCount() > 0 && current_time - modio::LAST_MOD_EVENT_POLL > modio::EVENT_POLL_INTERVAL)
    {
      modio::writeLogLine("Polling mod events", MODIO_DEBUGLEVEL_LOG);

      ModioFilterCreator filter;
      modioInitFilter(&filter);
      modioAddFilterMinField(&filter, (char *)"date_added", (char *)modio::toString(modio::LAST_MOD_EVENT_POLL).c_str());
      modioAddFilterSmallerThanField(&filter, (char *)"date_added", (char *)modio::toString(current_time).c_str());
      u32 installed_mods_size = modioGetInstalledModsCount();
      ModioInstalledMod *modio_installed_mods = new ModioInstalledMod[installed_mods_size];
      modioGetInstalledMods(modio_installed_mods);
      for (u32 i = 0; i < (u32)installed_mods_size; i++)
      {
        modioAddFilterInField(&filter, (char *)"mod_id", (char *)modio::toString(modio_installed_mods[i].mod_id).c_str());
      }
      modioGetAllEvents(NULL, filter, &modio::onGetAllEventsPoll);

      modio::LAST_MOD_EVENT_POLL = current_time;
      delete[] modio_installed_mods;
    }

    if (modioIsLoggedIn() && current_time - modio::LAST_USER_EVENT_POLL > modio::EVENT_POLL_INTERVAL)
    {
      modio::writeLogLine("Polling user events", MODIO_DEBUGLEVEL_LOG);

      ModioFilterCreator filter;
      modioInitFilter(&filter);
      modioAddFilterMinField(&filter, (char *)"date_added", (char *)modio::toString(modio::LAST_USER_EVENT_POLL).c_str());
      modioAddFilterSmallerThanField(&filter, (char *)"date_added", (char *)modio::toString(current_time).c_str());

      modioGetUserEvents(NULL, filter, &modio::onGetUserEventsPoll);

      modio::LAST_USER_EVENT_POLL = current_time;
    }
  }
}
} // namespace modio
