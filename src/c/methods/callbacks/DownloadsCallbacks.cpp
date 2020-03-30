#include "c/methods/callbacks/DownloadsCallbacks.h"
#include "Utility.h" // for hasKey

std::map<u32, CheckIfModsAreUpdatedParams *> check_if_mods_are_updated_callbacks;
std::map<u32, UpdateModsParams *> update_mods_callbacks;


void onModioCheckIfModsAreUpdated(void *object, ModioResponse response, ModioMod *mods, u32 mods_size)
{
  modio::writeLogLine("onModioCheckIfModsAreUpdate was returned", MODIO_DEBUGLEVEL_LOG);
  u32 call_number = *(u32*)object;

  if (response.code == 200)
  {
    std::vector<u32> mod_ids_that_need_update;
    for (u32 i = 0; i < mods_size; i++)
    {
      ModioInstalledMod installed_mod;
      modioGetInstalledMod(mods[i].id, &installed_mod);
      if (installed_mod.mod_id != 0)
      {
        if(installed_mod.mod.modfile.date_added < mods[i].modfile.date_added)
        {
          modio::writeLogLine("The following installed mod needs an update: " + modio::toString(mods[i].id), MODIO_DEBUGLEVEL_LOG);
          mod_ids_that_need_update.push_back(mods[i].id);
          modio::writeLogLine("Mod will be added to the download queue.", MODIO_DEBUGLEVEL_LOG);
          check_if_mods_are_updated_callbacks[call_number]->mods_are_updated = false;
        }else
        {
          modio::writeLogLine(modio::toString(mods[i].id) + "is up to date.", MODIO_DEBUGLEVEL_LOG);
        }
        
      }
      else
      {
        modio::writeLogLine("Mod is not installed, will be added to the download queue: " + modio::toString(mods[i].id), MODIO_DEBUGLEVEL_ERROR);
        mod_ids_that_need_update.push_back(mods[i].id);
        check_if_mods_are_updated_callbacks[call_number]->mods_are_updated = false;
      }
    }
    if(mod_ids_that_need_update.size() > 0)
    {
      modio::addModsToDownloadQueue(mod_ids_that_need_update);
    }
  }else
  {
    modio::writeLogLine("Could not retrieve mods data error code: " + modio::toString(response.code), MODIO_DEBUGLEVEL_ERROR);
    check_if_mods_are_updated_callbacks[call_number]->mods_are_updated = false;
  }
  modio::writeLogLine("onModioCheckIfModsAreUpdate finished", MODIO_DEBUGLEVEL_LOG);

  check_if_mods_are_updated_callbacks[call_number]->call_count--;
  if(check_if_mods_are_updated_callbacks[call_number]->call_count == 0)
  {
    check_if_mods_are_updated_callbacks[call_number]->callback(check_if_mods_are_updated_callbacks[call_number]->object,
                                                                response,
                                                                check_if_mods_are_updated_callbacks[call_number]->mods_are_updated);

    delete check_if_mods_are_updated_callbacks[call_number];
    check_if_mods_are_updated_callbacks.erase(call_number);
    delete (u32*)object;
  }
}

void onModioUpdateMods(void* object, ModioResponse response, bool mods_are_updated)
{
  u32 call_number = *(u32*)object;
  update_mods_callbacks[call_number]->callback(update_mods_callbacks[call_number]->object,
                                                              response,
                                                              mods_are_updated);
  delete update_mods_callbacks[call_number];
  delete (u32*)object;
    
}

void clearDownloadsCallbackParams()
{
  for (auto check_if_mods_are_updated_callback : check_if_mods_are_updated_callbacks)
    delete check_if_mods_are_updated_callback.second;
  check_if_mods_are_updated_callbacks.clear();
}
