#include "ModioUtility.h"

namespace modio
{
void onUpdateCurrentUser(void *object, ModioResponse response, ModioUser user)
{
  if (response.code >= 200 && response.code < 300)
  {
    modio::writeLogLine("Current user updated sucessfully.", MODIO_DEBUGLEVEL_LOG);
  }
  else
  {
    modio::writeLogLine("Could not update current user.", MODIO_DEBUGLEVEL_WARNING);
  }
}

void onAddModsToDownloadQueue(void *object, ModioResponse response, ModioMod *mods, u32 mods_size)
{
  if (response.code == 200)
  {
    for (u32 i = 0; i < mods_size; i++)
    {
      modio::curlwrapper::queueModDownload(mods[i]);
    }
  }
}

void onModsUpdateEvent(void *object, ModioResponse response, ModioMod *mods, u32 mods_size)
{
  if (response.code == 200)
  {
    for (u32 i = 0; i < mods_size; i++)
    {
      modio::Mod mod;
      mod.initialize(mods[i]);
      std::string mod_path_str = modio::getInstalledModPath(mod.id) + "modio.json";
      modio::writeJson(mod_path_str, modio::toJson(mod));
      modio::writeLogLine("Mod updated", MODIO_DEBUGLEVEL_LOG);
    }
  }
}

void updateModsCache(std::vector<u32> mod_ids)
{
  ModioFilterCreator filter;
  modioInitFilter(&filter);
  for (auto &mod_id : mod_ids)
  {
    modioAddFilterInField(&filter, (char *)"id", (char *)modio::toString(mod_id).c_str());
  }
  modioGetAllMods(NULL, filter, &onModsUpdateEvent);
  modioFreeFilter(&filter);
}

void addModsToDownloadQueue(std::vector<u32> mod_ids)
{
  ModioFilterCreator filter;
  modioInitFilter(&filter);
  for (auto &mod_id : mod_ids)
  {
    modioAddFilterInField(&filter, (char *)"id", (char *)modio::toString(mod_id).c_str());
  }
  modioGetAllMods(NULL, filter, &modio::onAddModsToDownloadQueue);
  modioFreeFilter(&filter);
}

void onGetAllEventsPoll(void *object, ModioResponse response, ModioModEvent *events_array, u32 events_array_size)
{
  if (response.code == 200)
  {
    modio::writeLogLine("Mod events polled", MODIO_DEBUGLEVEL_LOG);
    if (modio::event_listener_callback && events_array_size > 0)
      modio::event_listener_callback(response, events_array, events_array_size);

    std::vector<u32> mod_edited_ids;
    std::vector<u32> mod_to_download_queue_ids;
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
        for (auto installed_mod : modio::installed_mods)
        {
          if (modio::hasKey(installed_mod, "mod_id") && modio::hasKey(installed_mod, "date_updated") && installed_mod["mod_id"] == events_array[i].mod_id && installed_mod["date_updated"] >= events_array[i].date_added)
          {
            modio::writeLogLine("Modfile changed event detected but you already have a newer version installed, the modfile will not be downloaded. Mod id: " + modio::toString(events_array[i].mod_id), MODIO_DEBUGLEVEL_LOG);
          }
        }

        if (reinstall)
        {
          modio::writeLogLine("Modfile changed. Mod id: " + modio::toString(events_array[i].mod_id) + " Reisntalling...", MODIO_DEBUGLEVEL_LOG);
          mod_to_download_queue_ids.push_back(events_array[i].mod_id);
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
        modio::writeLogLine("Mod updated. Mod id: " + modio::toString(events_array[i].mod_id) + " Updating cache...", MODIO_DEBUGLEVEL_LOG);
        mod_edited_ids.push_back(events_array[i].mod_id);
        break;
      }
      }
    }
    if (mod_edited_ids.size() > 0)
      updateModsCache(mod_edited_ids);
    if (mod_to_download_queue_ids.size() > 0)
      addModsToDownloadQueue(mod_to_download_queue_ids);

    nlohmann::json event_polling_json = modio::openJson(modio::getModIODirectory() + "event_polling.json");
    event_polling_json["last_mod_event_poll"] = modio::LAST_MOD_EVENT_POLL;
    modio::writeJson(modio::getModIODirectory() + "event_polling.json", event_polling_json);
  }
  else
  {
    modio::writeLogLine("Could not poll mod events. Error code: " + modio::toString(response.code), MODIO_DEBUGLEVEL_ERROR);
  }
}

void onGetUserEventsPoll(void *object, ModioResponse response, ModioUserEvent *events_array, u32 events_array_size)
{
  if (response.code == 200)
  {
    if (modio::event_listener_callback && events_array_size > 0)
    {
      ModioModEvent *mod_events_array = new ModioModEvent[events_array_size];
      for(u32 i=0; i < events_array_size; i++)
      {
        mod_events_array[i].id = events_array[i].id;
        mod_events_array[i].mod_id = events_array[i].mod_id;
        mod_events_array[i].user_id = events_array[i].user_id;
        mod_events_array[i].event_type = events_array[i].event_type;
        mod_events_array[i].date_added = events_array[i].date_added;
      }

      modio::event_listener_callback(response, mod_events_array, events_array_size);

      for(u32 i=0; i < events_array_size; i++)
      {
        modioFreeModEvent(&mod_events_array[i]);
      }
      delete[] mod_events_array;
    }

    modio::writeLogLine("User events polled ", MODIO_DEBUGLEVEL_LOG);

    std::vector<u32> mod_to_download_queue_ids;
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
        modio::writeLogLine("Current User subscribed to a Mod. Mod id: " + modio::toString(events_array[i].mod_id) + " Installing...", MODIO_DEBUGLEVEL_LOG);
        std::string modfile_path_str = modio::getInstalledModPath(events_array[i].mod_id);
        if (modfile_path_str == "")
        {
          modio::writeLogLine("Installing mod. Id: " + modio::toString(events_array[i].mod_id), MODIO_DEBUGLEVEL_LOG);
          mod_to_download_queue_ids.push_back(events_array[i].mod_id);
        }
        break;
      }
      case MODIO_EVENT_USER_UNSUBSCRIBE:
      {
        modio::writeLogLine("Current User unsubscribed from a Mod. Mod id: " + modio::toString(events_array[i].mod_id) + " Uninstalling...", MODIO_DEBUGLEVEL_LOG);
        modioUninstallMod(events_array[i].mod_id);
        break;
      }
      }
    }
    if (mod_to_download_queue_ids.size() > 0)
      addModsToDownloadQueue(mod_to_download_queue_ids);
    nlohmann::json token_json = modio::openJson(modio::getModIODirectory() + "authentication.json");
    token_json["last_user_event_poll"] = modio::LAST_USER_EVENT_POLL;
    modio::writeJson(modio::getModIODirectory() + "authentication.json", token_json);
  }
  else
  {
    modio::writeLogLine("Could not poll user events. Error code: " + modio::toString(response.code), MODIO_DEBUGLEVEL_ERROR);
  }
}

void pollEvents()
{
  u32 current_time = modio::getCurrentTime();

  if (current_time >= modio::RETRY_AFTER)
  {
    if (modioGetAllInstalledModsCount() > 0 && current_time - modio::LAST_MOD_EVENT_POLL > modio::EVENT_POLL_INTERVAL)
    {
      modio::writeLogLine("Polling mod events", MODIO_DEBUGLEVEL_LOG);

      ModioFilterCreator filter;
      modioInitFilter(&filter);
      modioAddFilterMinField(&filter, (char *)"date_added", (char *)modio::toString(modio::LAST_MOD_EVENT_POLL).c_str());
      modioAddFilterSmallerThanField(&filter, (char *)"date_added", (char *)modio::toString(current_time).c_str());

      for (auto installed_mod : modio::installed_mods)
      {
        if (modio::hasKey(installed_mod, "mod_id"))
          modioAddFilterInField(&filter, (char *)"mod_id", (char *)modio::toString((u32)installed_mod["mod_id"]).c_str());
      }

      modioGetAllEvents(NULL, filter, &onGetAllEventsPoll);
      modioFreeFilter(&filter);

      modio::LAST_MOD_EVENT_POLL = current_time;
    }
    else if (current_time - modio::LAST_MOD_EVENT_POLL > modio::EVENT_POLL_INTERVAL)
    {
      nlohmann::json event_polling_json = modio::openJson(modio::getModIODirectory() + "event_polling.json");
      event_polling_json["last_mod_event_poll"] = current_time;
      modio::writeJson(modio::getModIODirectory() + "event_polling.json", event_polling_json);
    }

    if (modioIsLoggedIn() && current_time - modio::LAST_USER_EVENT_POLL > modio::EVENT_POLL_INTERVAL)
    {
      modio::writeLogLine("Polling user events", MODIO_DEBUGLEVEL_LOG);

      ModioFilterCreator filter;
      modioInitFilter(&filter);
      modioAddFilterFieldValue(&filter, (char*)"game_id", (char*)toString(modio::GAME_ID).c_str());
      modioAddFilterMinField(&filter, (char *)"date_added", (char *)modio::toString(modio::LAST_USER_EVENT_POLL).c_str());
      modioAddFilterSmallerThanField(&filter, (char *)"date_added", (char *)modio::toString(current_time).c_str());

      modioGetUserEvents(NULL, filter, &onGetUserEventsPoll);
      modioFreeFilter(&filter);

      modio::LAST_USER_EVENT_POLL = current_time;
    }
  }
}

void updateAuthenticatedUser(std::string access_token)
{
  modio::writeLogLine("Updating authenticated user.", MODIO_DEBUGLEVEL_LOG);
  modio::ACCESS_TOKEN = access_token;
  nlohmann::json authentication_json;
  authentication_json["access_token"] = access_token;
  modio::writeJson(modio::getModIODirectory() + "authentication.json", authentication_json);
  modioGetAuthenticatedUser(NULL, &modio::onUpdateCurrentUser);
}

void handleDownloadImageError(void *object, void (*callback)(void *object, ModioResponse modioresponse))
{
  ModioResponse response;
  nlohmann::json empty_json;
  modioInitResponse(&response, empty_json);
  callback(object, response);
  modioFreeResponse(&response);
}

} // namespace modio
