#include "ModIOSDK.h"

bool checkIfModIsStillInstalled(string path, int modfile_id)
{
  string modfile_json_path = path + "modio.json";
  std::ifstream modfile_file(modfile_json_path.c_str());
  if(!modfile_file.is_open())
  {
    return false;
  }
  json modfile_json;
  modfile_file >> modfile_json;
  int json_modfile_id = modfile_json["modfile_id"];
  return json_modfile_id == modfile_id;
}

void updateModfilesJson()
{
  std::ifstream modfiles_file(modio::getModIODirectory() + "modfiles.json");
  if(modfiles_file.is_open())
  {
    json modfiles_json;
    json resulting_json;
    modfiles_file >> modfiles_json;
    modfiles_json = modfiles_json["modfiles"];
    for(int i=0; i<(int)modfiles_json.size(); i++)
    {
      if(checkIfModIsStillInstalled(modfiles_json[i]["path"], modfiles_json[i]["id"]))
      {
        resulting_json["modfiles"].push_back(modfiles_json[i]);
      }
    }
    std::ofstream out(modio::getModIODirectory() + "modfiles.json");
    out<<setw(4)<<resulting_json<<endl;
    out.close();
  }
}

void modioInit(int game_id, char* api_key)
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

  updateModfilesJson();

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
