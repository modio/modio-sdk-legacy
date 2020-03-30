#include "c/methods/callbacks/DownloadsCallbacks.h"
#include "Utility.h" // for hasKey

std::map<u32, CheckIfModsAreUpdatedParams *> check_if_mods_are_updated_callbacks;


void onModioCheckIfModsAreUpdated(void *object, ModioResponse response, ModioMod *mods, u32 mods_size)
{
  modio::writeLogLine("onModioCheckIfModsAreUpdate was returned", MODIO_DEBUGLEVEL_LOG);
  bool mods_are_updated = true;
  if (response.code == 200)
  {
    std::vector<u32> mod_ids_that_need_update;
    for (u32 i = 0; i < mods_size; i++)
    {
      ModioInstalledMod installed_mod;
      modioGetInstalledMod(mods[i].id, &installed_mod);
      if (installed_mod.mod_id != 0)
      {
        if(installed_mod.date_updated < mods[i].date_updated)
        {
          modio::writeLogLine("The following installed mod needs an update: " + modio::toString(mods[i].id), MODIO_DEBUGLEVEL_LOG);
          mod_ids_that_need_update.push_back(mods[i].id);
          modio::writeLogLine("Mod will be added to the download queue.", MODIO_DEBUGLEVEL_LOG);
          mods_are_updated = false;
        }
      }
      else
      {
        modio::writeLogLine("Installed mod not found on mod.io: " + modio::toString(mods[i].id), MODIO_DEBUGLEVEL_ERROR);
        mods_are_updated = false;
      }
    }
    if(mod_ids_that_need_update.size() > 0)
    {
      modio::addModsToDownloadQueue(mod_ids_that_need_update);
    }
  }else
  {
    modio::writeLogLine("Could not retrieve mods data error code: " + modio::toString(response.code), MODIO_DEBUGLEVEL_ERROR);
    mods_are_updated = false;
  }
  modio::writeLogLine("onModioCheckIfModsAreUpdate finished", MODIO_DEBUGLEVEL_LOG);

  u32 call_number = *(u32*)object;
  check_if_mods_are_updated_callbacks[call_number]->callback(check_if_mods_are_updated_callbacks[call_number]->object, response, mods_are_updated);

  delete check_if_mods_are_updated_callbacks[call_number];
  check_if_mods_are_updated_callbacks.erase(call_number);
  delete (u32*)object;
}

void clearDownloadsCallbackParams()
{
  for (auto check_if_mods_are_updated_callback : check_if_mods_are_updated_callbacks)
    delete check_if_mods_are_updated_callback.second;
  check_if_mods_are_updated_callbacks.clear();
}
