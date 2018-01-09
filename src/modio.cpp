#include "modio.h"

void modioInit(u32 game_id, char* api_key)
{
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

  modio::updateModfilesJson();

  modio::createDirectory(modio::getModIODirectory());
  modio::createDirectory(modio::getModIODirectory() + "images/");
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

void modioProcess()
{
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
