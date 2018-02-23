#include "ModioUtility.h"

namespace modio
{
  void onModfileChangedEvent(void* object, ModioResponse response)
  {
    printf("On modfile changed response: %i\n",response.code);
  }

  void onModSubscriptionInstalled(void* object, ModioResponse response)
  {
    printf("On mod subsciption installed response: %i\n",response.code);
  }

  void onModUpdateEvent(void* object, ModioResponse response, ModioMod modio_mod)
  {
    char* mod_path = (char*)object;
    std::string mod_path_str = std::string(mod_path) + "modio.json";
    printf("On mod get response: %i\n",response.code);
    if(response.code == 200)
    {
      modio::Mod mod;
      mod.initialize(modio_mod);
      modio::writeJson(mod_path_str,mod.toJson());
    }
    if(mod_path)
      delete[] mod_path;
  }

  void onGetAllEventsPoll(void* object, ModioResponse response, ModioEvent* events_array, u32 events_array_size)
  {
    if(modio::callback)
      modio::callback(response, events_array, events_array_size);

    for(int i=0; i<(int)events_array_size; i++)
    {
      switch( events_array[i].event_type )
      {
        case MODIO_EVENT_UNDEFINED:
        // TODO: Log error
        break;
        case MODIO_EVENT_MODFILE_CHANGED:
        {
          // TODO: Reinstall modfile
          std::string modfile_path_str = modio::getInstalledModPath(events_array[i].mod_id);
          modioInstallMod(NULL, events_array[i].mod_id, (char*)modfile_path_str.c_str(), &modio::onModfileChangedEvent);
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
          // TODO: Update locally installed mods
          std::string mod_path_str = modio::getInstalledModPath(events_array[i].mod_id);
          char* mod_path = new char[mod_path_str.size() + 1];
          strcpy(mod_path, mod_path_str.c_str());
          modioGetMod(mod_path, events_array[i].mod_id, &modio::onModUpdateEvent);
          break;
        }
      }
    }
  }

  void onGetUserEventsPoll(void* object, ModioResponse response, ModioEvent* events_array, u32 events_array_size)
  {
    //TODO: Register User Callback
    //if(modio::callback)
    //  modio::callback(response, events_array, events_array_size);
    writeLogLine("User events polled ", MODIO_DEBUGLEVEL_LOG);

    for(int i=0; i<(int)events_array_size; i++)
    {
      switch( events_array[i].event_type )
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
          writeLogLine("Current User just subscribed to a Mod ", MODIO_DEBUGLEVEL_LOG);
          std::string modfile_path_str = modio::getInstalledModPath(events_array[i].mod_id);
          if(modfile_path_str == "")
          {
            writeLogLine("Installing mod. Id: " + modio::toString(events_array[i].mod_id), MODIO_DEBUGLEVEL_LOG);
            std::string modfile_path = modio::getModIODirectory() + "mods/" + modio::toString(events_array[i].mod_id);
            modioInstallMod(NULL, events_array[i].mod_id, (char*)modfile_path.c_str(), &modio::onModSubscriptionInstalled);
          }
          break;
        }
        case MODIO_EVENT_USER_UNSUBSCRIBE:
        {
          // TODO: N/A
          std::cout<<"Unsubscribed!"<<std::endl;
          modioUninstallMod(events_array[i].mod_id);

          break;
        }
      }
    }
  }

  void pollEvents()
  {
    u32 current_time = modio::getCurrentTime();

    if(current_time - modio::LAST_MOD_EVENT_POLL > modio::EVENT_POLL_INTERVAL)
    {
      ModioFilterCreator filter;
      modioInitFilter(&filter);
      modioAddFilterMinField(&filter, (char*)"date_added", (char*)modio::toString(modio::LAST_MOD_EVENT_POLL).c_str());
      modioAddFilterSmallerThanField(&filter, (char*)"date_added", (char*)modio::toString(current_time).c_str());

      modioGetAllEvents(NULL, filter, &modio::onGetAllEventsPoll);

      modio::LAST_MOD_EVENT_POLL = current_time;
    }

    if(current_time - modio::LAST_USER_EVENT_POLL > modio::EVENT_POLL_INTERVAL)
    {

      std::cout<<"User events polling"<<std::endl;

      ModioFilterCreator filter;
      modioInitFilter(&filter);
      modioAddFilterMinField(&filter, (char*)"date_added", (char*)modio::toString(modio::LAST_USER_EVENT_POLL).c_str());
      modioAddFilterSmallerThanField(&filter, (char*)"date_added", (char*)modio::toString(current_time).c_str());

      modioGetUserEvents(NULL, filter, &modio::onGetUserEventsPoll);

      modio::LAST_USER_EVENT_POLL = current_time;
    }
  }
}
