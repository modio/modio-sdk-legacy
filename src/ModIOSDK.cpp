#include "ModIOSDK.h"

namespace modio
{
  void init(int game_id, string api_key)
  {
    createDirectory(getModIODirectory());

    clearLog();
    curlwrapper::initCurl();

    writeLogLine("Initializing SDK", verbose);
    modio::GAME_ID = game_id;
    modio::API_KEY = api_key;
    modio::ACCESS_TOKEN = "";

    std::ifstream token_file(getModIODirectory() + "token.json");
    if(token_file.is_open())
    {
      json token_file_json;
      token_file >> token_file_json;
      if(token_file_json.find("access_token") != token_file_json.end())
      {
        modio::ACCESS_TOKEN = token_file_json["access_token"];
      }
    }

    createDirectory(getModIODirectory() + "images/");
    createDirectory(getModIODirectory() + "tmp/");
    writeLogLine("SDK Initialized", verbose);

    //TODO: Use retrived acess token when server does
    modio::ACCESS_TOKEN = "turupawn";
  }

  void init(int game_id, const char* api_key, const char* root_path)
  {
    ROOT_PATH = root_path;
    init(game_id, string(api_key));
  }

  void setDebugMode(DebugMode debug_mode)
  {
    DEBUG_LEVEL = debug_mode;
  }

  void shutdown()
  {
    curlwrapper::shutdownCurl();
  }

  CurrentDownloadInfo getCurrentDownloadInfo()
  {
    return curlwrapper::getCurrentDownloadInfo();
  }

  void pauseCurrentDownload()
  {
    curlwrapper::pauseCurrentDownload();
  }
}
