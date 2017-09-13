#include "ModworksSDK.h"

namespace modworks
{
  void init(int game_id, string api_key)
  {
    clearLog();

    initCurl();

    writeLogLine("Initializing SDK", verbose);
    modworks::game_id = game_id;
    modworks::api_key = api_key;
    access_token = "";

    std::ifstream token_file(".modworks/token.json");
    if(token_file.is_open())
    {
      json token_file_json;
      token_file >> token_file_json;
      if(token_file_json.find("access_token") != token_file_json.end())
      {
        access_token = token_file_json["access_token"];
      }
    }

    createDirectory(".modworks");
    createDirectory(".modworks/images");
    createDirectory(".modworks/tmp");
    writeLogLine("SDK Initialized", verbose);
  }
}
