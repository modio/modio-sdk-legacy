#include "c/methods/callbacks/DownloadsCallbacks.h"
#include "Utility.h" // for hasKey

std::map<u32, DownloadModfilesByIdParams *> download_modfiles_by_id_callbacks;
std::map<u32, DownloadSubscribedModfilesParams *> download_subscribed_modfiles_callbacks;


void onModioDownloadModfilesById(void *object, ModioResponse response, ModioMod *mods, u32 mods_size)
{
  modio::writeLogLine("onModioDownloadModfilesById response: " + modio::toString((u32)response.code), MODIO_DEBUGLEVEL_LOG);
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
          modio::writeLogLine("The following installed modfile needs an update and will be added to the download queue: " + modio::toString(mods[i].id), MODIO_DEBUGLEVEL_LOG);
          mod_ids_that_need_update.push_back(mods[i].id);
          download_modfiles_by_id_callbacks[call_number]->mods_are_updated = false;
        }else
        {
          modio::writeLogLine(modio::toString(mods[i].id) + " is up to date. Won't be downloaded.", MODIO_DEBUGLEVEL_LOG);
        }
      }
      else
      {
        modio::writeLogLine("Modfile is not installed, will be added to the download queue: " + modio::toString(mods[i].id), MODIO_DEBUGLEVEL_LOG);
        mod_ids_that_need_update.push_back(mods[i].id);
        download_modfiles_by_id_callbacks[call_number]->mods_are_updated = false;
      }
    }
    if(mod_ids_that_need_update.size() > 0)
    {
      modio::writeLogLine(modio::toString((u32)mod_ids_that_need_update.size()) + " mods will be added to the download queue", MODIO_DEBUGLEVEL_LOG);
      modio::addModsToDownloadQueue(mod_ids_that_need_update);
    }else
    {
      modio::writeLogLine("No mods will be added to the download queue", MODIO_DEBUGLEVEL_LOG);
    }
    
  }else
  {
    modio::writeLogLine("Could not retrieve mods data error code: " + modio::toString(response.code), MODIO_DEBUGLEVEL_ERROR);
    download_modfiles_by_id_callbacks[call_number]->mods_are_updated = false;
  }

  download_modfiles_by_id_callbacks[call_number]->call_count--;
  if(download_modfiles_by_id_callbacks[call_number]->call_count == 0)
  {
    modio::writeLogLine("Last DownloadModfilesById call found. Triggering callback and cleaning", MODIO_DEBUGLEVEL_LOG);
    download_modfiles_by_id_callbacks[call_number]->callback(download_modfiles_by_id_callbacks[call_number]->object,
                                                                response,
                                                                download_modfiles_by_id_callbacks[call_number]->mods_are_updated);

    delete download_modfiles_by_id_callbacks[call_number];
    download_modfiles_by_id_callbacks.erase(call_number);
    delete (u32*)object;
  }else
  {
    modio::writeLogLine("This is a paginated call. No callback nor cleaning will be done now", MODIO_DEBUGLEVEL_LOG);
  }
  

  modio::writeLogLine("onModioDownloadModfilesById call finished", MODIO_DEBUGLEVEL_LOG);
}

void onModioDownloadSubscribedModfiles(void* object, ModioResponse response, ModioMod *mods, u32 mods_size)
{
  modio::writeLogLine("onModioDownloadSubscribedModfiles response: " + modio::toString((u32)response.code), MODIO_DEBUGLEVEL_LOG);
  u32 call_number = *((u32*)object);
  if (response.code >= 200 && response.code < 300)
  {
    for(u32 i=0; i<mods_size; i++)
    {
      modio::writeLogLine("User is subscribed to " + modio::toString((u32)mods[i].id), MODIO_DEBUGLEVEL_LOG);
      download_subscribed_modfiles_callbacks[call_number]->mod_ids.push_back(mods[i].id);
    }

    download_subscribed_modfiles_callbacks[call_number]->pending_call_count--;
    if(response.result_offset + response.result_count < response.result_total)
    {
      modio::writeLogLine("Retrieved more than 100 mods. This call will be paginated.", MODIO_DEBUGLEVEL_LOG);
      download_subscribed_modfiles_callbacks[call_number]->pending_call_count++;
      ModioFilterCreator filter;
      modioInitFilter(&filter);
      modioSetFilterOffset(&filter, response.result_offset + response.result_count);
      modioGetUserSubscriptions(object, filter, &onModioDownloadSubscribedModfiles);
      modioFreeFilter(&filter);
    }
    
    if(download_subscribed_modfiles_callbacks[call_number]->pending_call_count == 0)
    {
      modio::writeLogLine("No more pending calls queued for mod subsciption retrieval, doing final process", MODIO_DEBUGLEVEL_LOG);

      if(download_subscribed_modfiles_callbacks[call_number]->uninstall_unsubscribed)
      {
        modio::writeLogLine("Unsubscribed mods will be uninstalled.", MODIO_DEBUGLEVEL_LOG);
        for(auto installed_mod_json : modio::installed_mods)
        {
          if(!std::count(download_subscribed_modfiles_callbacks[call_number]->mod_ids.begin(),
                          download_subscribed_modfiles_callbacks[call_number]->mod_ids.end(),
                          (u32)installed_mod_json["mod_id"]))
          {
            modio::writeLogLine(modio::toString((u32)installed_mod_json["mod_id"]) + " will be uninstalled", MODIO_DEBUGLEVEL_LOG);
            modioUninstallMod((u32)installed_mod_json["mod_id"]);
          }
        }
      }

      modio::writeLogLine("converting to array", MODIO_DEBUGLEVEL_LOG);

      u32* mod_ids = new u32[download_subscribed_modfiles_callbacks[call_number]->mod_ids.size()];
      for(int i=0; i<download_subscribed_modfiles_callbacks[call_number]->mod_ids.size(); i++)
      {
        mod_ids[i] = download_subscribed_modfiles_callbacks[call_number]->mod_ids[i];
      }

      modio::writeLogLine("internal modioDownloadModfilesById call", MODIO_DEBUGLEVEL_LOG);

      modioDownloadModfilesById(download_subscribed_modfiles_callbacks[call_number]->object,
                                  mod_ids,
                                  (u32)download_subscribed_modfiles_callbacks[call_number]->mod_ids.size(),
                                  download_subscribed_modfiles_callbacks[call_number]->callback);
      
      modio::writeLogLine("cleanining up onModioDownloadSubscribedModfiles", MODIO_DEBUGLEVEL_LOG);

      delete[] mod_ids;
      delete download_subscribed_modfiles_callbacks[call_number];
      delete (u32*)object;
    }
  }
  modio::writeLogLine("onModioDownloadSubscribedModfiles finished", MODIO_DEBUGLEVEL_LOG);
}

void clearDownloadsCallbackParams()
{
  for (auto download_modfiles_by_id_callback : download_modfiles_by_id_callbacks)
    delete download_modfiles_by_id_callback.second;
  download_modfiles_by_id_callbacks.clear();
}
