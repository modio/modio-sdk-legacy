#include "modio.h"

void modioInit(u32 environment, u32 game_id, char* api_key)
{
  if(environment == MODIO_ENVIRONMENT_TEST)
  {
    modio::MODIO_URL = "https://api.test.mod.io/";
  }
  modio::clearLog();

  modio::curlwrapper::initCurl();

  modio::writeLogLine("Initializing SDK", MODIO_DEBUGLEVEL_LOG);
  modio::GAME_ID = game_id;
  modio::API_KEY = api_key;
  modio::ACCESS_TOKEN = "";

  std::ifstream token_file(modio::getModIODirectory() + "token.json");
  if(token_file.is_open())
  {
    json token_file_json;
    token_file >> token_file_json;
    if(token_file_json.find("access_token") != token_file_json.end())
    {
      modio::ACCESS_TOKEN = token_file_json["access_token"];
    }
  }

  modio::updateInstalledModsJson();

  modio::createDirectory(modio::getModIODirectory());
  modio::createDirectory(modio::getModIODirectory() + "cache/");
  modio::createDirectory(modio::getModIODirectory() + "tmp/");
  modio::writeLogLine("SDK Initialized", MODIO_DEBUGLEVEL_LOG);
}
/*
void init(int game_id, char* api_key, char* root_path)
{
  ROOT_PATH = root_path;
  init(game_id, api_key);
}
*/

void modioSetDebugLevel(unsigned int debug_level)
{
  modio::DEBUG_LEVEL = debug_level;
}

void modioShutdown()
{
  modio::curlwrapper::shutdownCurl();
}

/*
CurrentDownloadInfo modioGetCurrentDownloadInfo()
{
  return curlwrapper::getCurrentDownloadInfo();
}
*/

void modioPauseCurrentDownload()
{
  modio::curlwrapper::pauseCurrentDownload();
}

void onGetAllModEvents(void* object, ModioResponse response, ModioModEvent* mod_events_array, u32 mod_events_array_size)
{
  printf("Get events response: %i\n", response.code);
  if(response.code == 200)
  {
    printf("Listing events:\n");

    for(u32 i=0; i < mod_events_array_size; i++)
    {
      std::cout<<"Id"<<mod_events_array[i].id<<std::endl;
      std::cout<<"Date added"<<mod_events_array[i].date_added<<std::endl;
      std::cout<<"Event type"<<mod_events_array[i].event_type<<std::endl;
      std::cout<<"Mod id"<<mod_events_array[i].mod_id<<std::endl;
    }
  }
}

void modioProcess()
{
  u32 current_time = modio::getCurrentTime();
  if(current_time - modio::LAST_EVENT_POLL > 5)
  {
    modio::LAST_EVENT_POLL = current_time;
    modioGetAllModEvents(NULL,&onGetAllModEvents);
  }
  modio::curlwrapper::process();
}

void modioSleep(u32 milliseconds)
{
  #ifdef LINUX
    usleep(milliseconds * 1000);
  #endif
  #ifdef WINDOWS
    Sleep(milliseconds);
  #endif
  #ifdef OSX
    usleep(milliseconds * 1000);
  #endif
}
