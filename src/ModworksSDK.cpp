#include "ModworksSDK.h"

namespace modworks
{
  SDK::SDK(int game_id, string api_key)
  {
    writeLogLine("Initializing SDK", verbose);
    this->game_id = game_id;
    this->api_key = api_key;

    createDirectory(".modworks");
    createDirectory(".modworks/images");
    createDirectory(".modworks/tmp");
    writeLogLine("SDK Initialized", verbose);
  }

  void SDK::getMods(function< void(vector<Mod*>) > callback)
  {
    writeLogLine("getMods call", verbose);
    vector<string> headers;
    headers.push_back("Authorization: Bearer Turupawn");
    string url = string("https://api.mod.works/v1/games/") + toString(game_id) + "/mods";

    int call_count = getCallCount();
    advanceCallCount();

    std::thread get_json_thread(getJson, url, headers, callback, call_count);
    get_json_thread.detach();
    writeLogLine("getJson thread detached", verbose);
  }

  void SDK::emailRequest(string email, function< void(int response) > callback)
  {
    map<string, string> data;
    data["api_key"] = api_key;
    data["email"] = email;
    modworks::post("https://api.mod.works/oauth/emailrequest?shhh=secret",data, callback);
  }

  void SDK::emailExchange(string security_code, function< void(int response) > callback)
  {
    map<string, string> data;
    data["api_key"] = api_key;
    data["security_code"] = security_code;
    modworks::post("https://api.mod.works/oauth/emailexchange?shhh=secret",data, callback);
  }
}
