#include "ModioUtility.h"
#include <stddef.h>
#include <map>
#include <set>
#include "c++/schemas/Mod.h"
#include "c/schemas/ModioModEvent.h"
#include "c/schemas/ModioMod.h"
#include "c/schemas/ModioModfile.h"
#include "c/schemas/ModioUser.h"
#include "dependencies/nlohmann/json.hpp"
#include "ModUtility.h"
#include "Globals.h"
#include "Utility.h"
#include "c/ModioC.h"
#include "c/schemas/ModioResponse.h"
#include "wrappers/CurlWrapper.h"

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

void onUpdateCurrentUserRatings(void *object, ModioResponse response, ModioRating *ratings_array, u32 ratings_array_size)
{
  if(response.result_offset == 0) /* Clear only if is first result page */
    modio::current_user_ratings.clear();

  if (response.code >= 200 && response.code < 300)
  {
    modio::writeLogLine("Current user ratings retrieved sucessfully.", MODIO_DEBUGLEVEL_LOG);
    for(u32 i=0; i<ratings_array_size; i++)
    {
      if(ratings_array[i].rating == 1)
        modio::current_user_ratings[ratings_array[i].mod_id] = MODIO_RATING_POSITIVE;
      else if(ratings_array[i].rating == -1)
        modio::current_user_ratings[ratings_array[i].mod_id] = MODIO_RATING_NEGATIVE;
      else
        modio::current_user_ratings[ratings_array[i].mod_id] = MODIO_RATING_UNDEFINED;
    }

    if(response.result_offset + response.result_count < response.result_total)
    {
      modio::writeLogLine("Paginated response, retrieving next page...", MODIO_DEBUGLEVEL_LOG);
      ModioFilterCreator filter;
      modioInitFilter(&filter);
      modioSetFilterOffset(&filter, response.result_offset + response.result_count);
      modioGetUserRatings(NULL, filter, &modio::onUpdateCurrentUserRatings);
      modioFreeFilter(&filter);
    }
  }
  else
  {
    modio::writeLogLine("Could not update current user ratings.", MODIO_DEBUGLEVEL_WARNING);
  }
}

void onUpdateCurrentUserSubscriptions(void* object, ModioResponse response, ModioMod *mods, u32 mods_size)
{
  if(response.result_offset == 0) /* Clear only if is first result page */
    modio::current_user_subscriptions.clear();

  if (response.code >= 200 && response.code < 300)
  {
    modio::writeLogLine("Current user subscriptions retrieved sucessfully.", MODIO_DEBUGLEVEL_LOG);

    std::string subscription_logs = "";
    for(u32 i=0; i<mods_size; i++)
    {
      modio::current_user_subscriptions.insert(mods[i].id);
      subscription_logs += modio::toString(mods[i].id) + ",";
    }

    modio::writeLogLine("You are subscribed to the following mods: " + subscription_logs, MODIO_DEBUGLEVEL_LOG);

    if(response.result_offset + response.result_count < response.result_total)
    {
      modio::writeLogLine("Paginated response, retrieving next page...", MODIO_DEBUGLEVEL_LOG);
      ModioFilterCreator filter;
      modioInitFilter(&filter);
      modioSetFilterOffset(&filter, response.result_offset + response.result_count);
      modioGetUserSubscriptions(NULL, filter, &modio::onUpdateCurrentUserSubscriptions);
      modioFreeFilter(&filter);
    }

    //modioDownloadSubscribedModfiles(NULL, false, &modio::onInitDownloadSubscribedModfiles);
  }
  else
  {
    modio::writeLogLine("Could not update current user subscriptions.", MODIO_DEBUGLEVEL_WARNING);
  }
}

static void onAddModsToDownloadQueue(void *object, ModioResponse response, ModioMod *mods, u32 mods_size)
{
  std::vector<int>* ptr_mod_ids = (std::vector<int>*)object;
  if (response.code == 200)
  {
    modio::writeLogLine("Mod queue data retrived successfully", MODIO_DEBUGLEVEL_LOG);

    for (u32 i = 0; i < mods_size; i++)
    {
      modio::curlwrapper::queueModDownload(mods[i]);
    }

    if(response.result_offset + response.result_count < response.result_total)
    {
      modio::writeLogLine("Paginated response, retrieving next page...", MODIO_DEBUGLEVEL_LOG);
      ModioFilterCreator filter;
      modioInitFilter(&filter);
      for (auto &mod_id : *ptr_mod_ids)
      {
        modioAddFilterInField(&filter, "id", modio::toString(mod_id).c_str());
      }
      modioSetFilterOffset(&filter, response.result_offset + response.result_count);
      modioGetAllMods(ptr_mod_ids, filter, &modio::onAddModsToDownloadQueue);
      modioFreeFilter(&filter);
    }else
    {
      delete ptr_mod_ids;
    }
  }else
  {
    modio::writeLogLine("Error retrieving mod queue data", MODIO_DEBUGLEVEL_ERROR);
    delete ptr_mod_ids;
  }
}

static void onModsUpdateEvent(void *object, ModioResponse response, ModioMod *mods, u32 mods_size)
{
  std::vector<int>* ptr_mod_ids = (std::vector<int>*)object;
  if (response.code == 200)
  {
    modio::writeLogLine("Updated mods data retrived successfully", MODIO_DEBUGLEVEL_LOG);
    for (u32 i = 0; i < mods_size; i++)
    {
      modio::Mod mod;
      mod.initialize(mods[i]);
      std::string mod_path_str = modio::getInstalledModPath(mod.id) + "modio.json";
      modio::writeJson(mod_path_str, modio::toJson(mod));
      modio::writeLogLine("Mod updated", MODIO_DEBUGLEVEL_LOG);
    }

    if(response.result_offset + response.result_count < response.result_total)
    {
      modio::writeLogLine("Paginated response, retrieving next page...", MODIO_DEBUGLEVEL_LOG);
      ModioFilterCreator filter;
      modioInitFilter(&filter);
      for (auto &mod_id : *ptr_mod_ids)
      {
        modioAddFilterInField(&filter, "id", modio::toString(mod_id).c_str());
      }
      modioSetFilterOffset(&filter, response.result_offset + response.result_count);
      modioGetAllMods(ptr_mod_ids, filter, &onModsUpdateEvent);
      modioFreeFilter(&filter);
    }else
    {
      delete ptr_mod_ids;
    }
  }else
  {
    modio::writeLogLine("Could not retrive updated mods data", MODIO_DEBUGLEVEL_ERROR);
    delete ptr_mod_ids;
  }
}

void handleUnsubscription(u32 mod_id)
{
  modioUninstallMod(mod_id);
  modioCancelModDownload(mod_id);
  modio::curlwrapper::removeDownloadedMod(mod_id);
}

void updateModsCache(std::vector<u32> mod_ids)
{
  ModioFilterCreator filter;
  modioInitFilter(&filter);

  std::vector<int>* ptr_mod_ids = new std::vector<int>();

  for (auto &mod_id : mod_ids)
  {
    modioAddFilterInField(&filter, "id", modio::toString(mod_id).c_str());
    ptr_mod_ids->push_back(mod_id);
  }

  modioGetAllMods(ptr_mod_ids, filter, &onModsUpdateEvent);
  modioFreeFilter(&filter);
}

void addModsToDownloadQueue(std::vector<u32> mod_ids)
{
  if(mod_ids.size() < 0)
  {
    modio::writeLogLine("Called addModsToDownloadQueue with an empty mod list", MODIO_DEBUGLEVEL_ERROR);
    return;
  }
  ModioFilterCreator filter;
  modioInitFilter(&filter);

  std::vector<int>* ptr_mod_ids = new std::vector<int>();

  for (auto &mod_id : mod_ids)
  {
    modioAddFilterInField(&filter, "id", modio::toString(mod_id).c_str());
    ptr_mod_ids->push_back(mod_id);
  }

  modioGetAllMods(ptr_mod_ids, filter, &modio::onAddModsToDownloadQueue);
  modioFreeFilter(&filter);
}

static void onGetAllEventsPoll(void *object, ModioResponse response, ModioModEvent *events_array, u32 events_array_size)
{
  u32* last_mod_event_poll_id_ptr = (u32*)object;
  if (response.code == 200)
  {
    modio::writeLogLine("Mod events polled", MODIO_DEBUGLEVEL_LOG);

    std::vector<u32> mod_edited_ids;
    std::vector<u32> mod_to_download_queue_ids;
    std::vector<u32> mod_deleted_ids;
    if(events_array_size > 0)
      modio::clearCache();
    for (size_t i = 0; i < events_array_size; i++)
    {
      if(events_array[i].id > modio::LAST_MOD_EVENT_POLL_ID)
      {
        modio::writeLogLine("Mod event id polled: " + modio::toString(events_array[i].id), MODIO_DEBUGLEVEL_LOG);
        modio::LAST_MOD_EVENT_POLL_ID = events_array[i].id;
      }

      switch (events_array[i].event_type)
      {
      case MODIO_EVENT_UNDEFINED:
        // TODO: Log error
        break;
      case MODIO_EVENT_MODFILE_CHANGED:
      {
        modio::writeLogLine("Modfile changed. Mod id: " + modio::toString(events_array[i].mod_id), MODIO_DEBUGLEVEL_LOG);
        modio::writeLogLine(" Adding to the download queue...", MODIO_DEBUGLEVEL_LOG);
        mod_to_download_queue_ids.push_back(events_array[i].mod_id);
        break;
      }
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
        modio::writeLogLine("Mod edited. Mod id: " + modio::toString(events_array[i].mod_id), MODIO_DEBUGLEVEL_LOG);
        /* TODO: Re-enable local mod profile update? */
        //modio::writeLogLine("Mod updated. Mod id: " + modio::toString(events_array[i].mod_id) + " Updating cache...", MODIO_DEBUGLEVEL_LOG);
        //mod_edited_ids.push_back(events_array[i].mod_id);
        break;
      }
      case MODIO_EVENT_MOD_DELETED:
      {
        modio::writeLogLine("Mod deleted. Mod id: " + modio::toString(events_array[i].mod_id) + " Uninstalling...", MODIO_DEBUGLEVEL_LOG);
        mod_deleted_ids.push_back(events_array[i].mod_id);
      }
      }
    }
    /* TODO: Re-enable mod profile update? */
    //if (mod_edited_ids.size() > 0)
    //  updateModsCache(mod_edited_ids);
    size_t deleted_mod_count = mod_deleted_ids.size();
    for (size_t i = 0; i < deleted_mod_count; ++i)
    {
      modioUninstallMod(mod_deleted_ids[i]);
    }

    if (mod_to_download_queue_ids.size() > 0)
      addModsToDownloadQueue(mod_to_download_queue_ids);

    nlohmann::json event_polling_json = modio::openJson(modio::getModIODirectory() + "event_polling.json");
    event_polling_json["last_mod_event_poll_id"] = modio::LAST_MOD_EVENT_POLL_ID;
    modio::writeJson(modio::getModIODirectory() + "event_polling.json", event_polling_json);

    if (modio::event_listener_callback && events_array_size > 0)
    {
      modio::writeLogLine("Triggering user callback listener", MODIO_DEBUGLEVEL_LOG);
      modio::event_listener_callback(response, events_array, events_array_size);
    }

    if(response.result_offset + response.result_count < response.result_total)
    {
      modio::writeLogLine("Paginated response, retrieving next page...", MODIO_DEBUGLEVEL_LOG);
      ModioFilterCreator filter;
      modioInitFilter(&filter);
      modioAddFilterGreaterThanField(&filter, "id", modio::toString(*last_mod_event_poll_id_ptr).c_str());

      for (auto installed_mod : modio::installed_mods)
      {
        if (modio::hasKey(installed_mod, "mod_id"))
          modioAddFilterInField(&filter, "mod_id", modio::toString((u32)installed_mod["mod_id"]).c_str());
      }
      modioSetFilterOffset(&filter, response.result_offset + response.result_count);
      modioGetAllEvents(last_mod_event_poll_id_ptr, filter, &onGetAllEventsPoll);
      modioFreeFilter(&filter);
    }else
    {
      delete last_mod_event_poll_id_ptr;
    }
  }
  else
  {
    modio::writeLogLine("Could not poll mod events. Error code: " + modio::toString(response.code), MODIO_DEBUGLEVEL_ERROR);
    delete last_mod_event_poll_id_ptr;
  }
}

static void onGetUserEventsPoll(void *object, ModioResponse response, ModioUserEvent *events_array, u32 events_array_size)
{
  u32* last_user_event_poll_id_ptr = (u32*)object;
  if (response.code == 200)
  {
    modio::writeLogLine("User events polled ", MODIO_DEBUGLEVEL_LOG);

    std::vector<u32> mod_to_download_queue_ids;
    if(events_array_size > 0)
      modio::clearCache();
    for (size_t i = 0; i < events_array_size; i++)
    {
      if(events_array[i].id > modio::LAST_USER_EVENT_POLL_ID)
      {
        modio::writeLogLine("User event id polled: " + modio::toString(events_array[i].id), MODIO_DEBUGLEVEL_LOG);
        modio::LAST_USER_EVENT_POLL_ID = events_array[i].id;
      }

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
        modio::current_user_subscriptions.insert(events_array[i].mod_id);
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
        modio::writeLogLine("Mod unsubscription event detected. Mod id: " + modio::toString(events_array[i].mod_id), MODIO_DEBUGLEVEL_LOG);
        handleUnsubscription(events_array[i].mod_id);
        break;
      }
      }
    }
    if (mod_to_download_queue_ids.size() > 0)
      addModsToDownloadQueue(mod_to_download_queue_ids);
    nlohmann::json token_json = modio::openJson(modio::getModIODirectory() + "authentication.json");
    token_json["last_user_event_poll_id"] = modio::LAST_USER_EVENT_POLL_ID;
    modio::writeJson(modio::getModIODirectory() + "authentication.json", token_json);

    if (modio::event_listener_callback && events_array_size > 0)
    {
      modio::writeLogLine("Triggering event callback listener", MODIO_DEBUGLEVEL_LOG);

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

    if(response.result_offset + response.result_count < response.result_total)
    {
      modio::writeLogLine("Paginated response, retrieving next pagee...", MODIO_DEBUGLEVEL_LOG);
      ModioFilterCreator filter;
      modio::writeLogLine("Last id: " + modio::toString(*last_user_event_poll_id_ptr), MODIO_DEBUGLEVEL_LOG);
      modioInitFilter(&filter);
      modioAddFilterGreaterThanField(&filter, "id", modio::toString(*last_user_event_poll_id_ptr).c_str());
      modioSetFilterOffset(&filter, response.result_offset + response.result_count);
      modioGetUserEvents(last_user_event_poll_id_ptr, filter, &onGetUserEventsPoll);
      modioFreeFilter(&filter);
    }else
    {
      delete last_user_event_poll_id_ptr;
    }
  }
  else
  {
    modio::writeLogLine("Could not poll user events. Error code: " + modio::toString(response.code), MODIO_DEBUGLEVEL_ERROR);
    delete last_user_event_poll_id_ptr;
  }
}

void pollUserEvents(u32 poll_time)
{
  modio::writeLogLine("Polling user events", MODIO_DEBUGLEVEL_LOG);

  ModioFilterCreator filter;
  modioInitFilter(&filter);
  //modioAddFilterMinField(&filter, "date_added", modio::toString(modio::LAST_USER_EVENT_POLL).c_str());
  modioAddFilterGreaterThanField(&filter, "id", modio::toString(modio::LAST_USER_EVENT_POLL_ID).c_str());

  u32 *last_user_event_poll_id_ptr = new u32;
  *last_user_event_poll_id_ptr = (u32)modio::LAST_USER_EVENT_POLL_ID;

  modioGetUserEvents(last_user_event_poll_id_ptr, filter, &onGetUserEventsPoll);
  modioFreeFilter(&filter);

  modio::LAST_USER_EVENT_POLL_TIME = poll_time;
}

void pollInstalledModsEvents(u32 poll_time)
{
  modio::writeLogLine("Polling mod events", MODIO_DEBUGLEVEL_LOG);

  ModioFilterCreator filter;
  modioInitFilter(&filter);
  modioAddFilterGreaterThanField(&filter, "id", modio::toString(modio::LAST_MOD_EVENT_POLL_ID).c_str());

  for (auto installed_mod : modio::installed_mods)
  {
    if (modio::hasKey(installed_mod, "mod_id"))
      modioAddFilterInField(&filter, "mod_id", modio::toString((u32)installed_mod["mod_id"]).c_str());
  }

  u32* last_mod_event_poll_id_ptr = new u32;
  *last_mod_event_poll_id_ptr = modio::LAST_MOD_EVENT_POLL_ID;

  modioGetAllEvents(last_mod_event_poll_id_ptr, filter, &onGetAllEventsPoll);
  modioFreeFilter(&filter);

  modio::LAST_MOD_EVENT_POLL_TIME = poll_time;
}

void updateAuthenticatedUser(std::string access_token)
{
  modio::writeLogLine("Updating authenticated user.", MODIO_DEBUGLEVEL_LOG);
  modio::clearCache();
  modio::ACCESS_TOKEN = access_token;
  nlohmann::json authentication_json;
  authentication_json["access_token"] = access_token;
  modio::writeJson(modio::getModIODirectory() + "authentication.json", authentication_json);
  modioGetAuthenticatedUser(NULL, &modio::onUpdateCurrentUser);
  modio::updateUserRatings();
  modio::updateUserSubscriptions();
}

void updateUserRatings()
{
  ModioFilterCreator filter;
  modioInitFilter(&filter);
  modioGetUserRatings(NULL, filter, &modio::onUpdateCurrentUserRatings);
  modioFreeFilter(&filter);
}

void updateUserSubscriptions()
{
  ModioFilterCreator filter;
  modioInitFilter(&filter);
  modioGetUserSubscriptions(NULL, filter, &modio::onUpdateCurrentUserSubscriptions);
  modioFreeFilter(&filter);
}

void addGameIdFilter(ModioFilterCreator &filter)
{
  if(!modio::RETRIEVE_MODS_FROM_OTHER_GAMES)
    modioAddFilterFieldValue(&filter, "game_id", modio::toString(modio::GAME_ID).c_str());
}

void handleDownloadImageError(void *object, void (*callback)(void *object, ModioResponse modioresponse))
{
  ModioResponse response;
  nlohmann::json empty_json;
  modioInitResponse(&response, empty_json);
  callback(object, response);
  modioFreeResponse(&response);
}

ModioResponse createUnauthorizedResponse()
{
  modio::writeLogLine("Unauthorized local request found. 401 will be returned", MODIO_DEBUGLEVEL_LOG);

  ModioResponse response;
  nlohmann::json empty_json;

  modioInitResponse(&response, empty_json);
  response.code = 401;

  return response;
}

void processGenericLocalUnauthorizedRequest(void* object, void(*callback)(void* object, ModioResponse response))
{
  ModioResponse response = createUnauthorizedResponse();

  callback(object, response);

  modioFreeResponse(&response);
}

void processLocalUnauthorizedRequestModParam(void* object, void (*callback)(void *object, ModioResponse response, ModioMod mod))
{
  ModioResponse response = createUnauthorizedResponse();

  ModioMod mod;
  nlohmann::json empty_json;
  modioInitMod(&mod, empty_json);

  callback(object, response, mod);

  modioFreeResponse(&response);
  modioFreeMod(&mod);
}

void processLocalUnauthorizedRequestModfileParam(void* object, void (*callback)(void *object, ModioResponse response, ModioModfile modfile))
{
  ModioResponse response = createUnauthorizedResponse();

  ModioModfile modfile;
  nlohmann::json empty_json;
  modioInitModfile(&modfile, empty_json);

  callback(object, response, modfile);

  modioFreeResponse(&response);
  modioFreeModfile(&modfile);
}

void processLocalUnauthorizedRequestBoolParam(void* object, void (*callback)(void *object, ModioResponse response, bool))
{
  ModioResponse response = createUnauthorizedResponse();

  callback(object, response, false);

  modioFreeResponse(&response);
}

void processLocalUnauthorizedRequestUserParam(void* object, void (*callback)(void *object, ModioResponse response, ModioUser user))
{
  ModioResponse response = createUnauthorizedResponse();

  ModioUser user;
  nlohmann::json empty_json;
  modioInitUser(&user, empty_json);

  callback(object, response, user);

  modioFreeResponse(&response);
  modioFreeUser(&user);
}

void processLocalUnauthorizedRequestModsParam(void* object, void (*callback)(void *object, ModioResponse response, ModioMod mods[], u32 mods_size))
{
  ModioResponse response = createUnauthorizedResponse();

  callback(object, response, NULL, 0);

  modioFreeResponse(&response);
}

void processLocalUnauthorizedRequestUserEventsParam(void* object, void (*callback)(void *object, ModioResponse response, ModioUserEvent* events_array, u32 events_array_size))
{
  ModioResponse response = createUnauthorizedResponse();

  callback(object, response, NULL, 0);

  modioFreeResponse(&response);
}

void processLocalUnauthorizedRequestGamesParam(void* object, void (*callback)(void *object, ModioResponse response, ModioGame games[], u32 games_size))
{
  ModioResponse response = createUnauthorizedResponse();

  callback(object, response, NULL, 0);

  modioFreeResponse(&response);
}

void processLocalUnauthorizedRequestModfilesParam(void* object, void (*callback)(void *object, ModioResponse response, ModioModfile modfiles[], u32 modfiles_size))
{
  ModioResponse response = createUnauthorizedResponse();

  callback(object, response, NULL, 0);

  modioFreeResponse(&response);
}

void processLocalUnauthorizedRequestRatingsParam(void* object, void (*callback)(void *object, ModioResponse response, ModioRating ratings[], u32 ratings_size))
{
  ModioResponse response = createUnauthorizedResponse();

  callback(object, response, NULL, 0);

  modioFreeResponse(&response);
}

} // namespace modio
