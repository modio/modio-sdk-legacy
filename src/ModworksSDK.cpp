#include "ModworksSDK.h"

namespace modworks
{
  SDK::SDK(int game_id, string current_user)
  {
    writeLogLine("Initializing SDK", verbose);
    this->game_id = game_id;
    this->current_user = current_user;

    createDirectory(".modworks");
    createDirectory(".modworks/images");
    createDirectory(".modworks/tmp");
    writeLogLine("SDK Initialized", verbose);
  }

  void SDK::getMods(function< void(vector<Mod*>) > callback)
  {
    writeLogLine("getMods call", verbose);
    vector<string> headers;
    headers.push_back(string("Authorization: Bearer ") + current_user);
    string url = string("https://api.mod.works/v1/games/") + toString(game_id) + "/mods";

    int call_count = getCallCount();
    advanceCallCount();

    std::thread get_json_thread(getJson, url, headers, callback, call_count);
    get_json_thread.detach();
    writeLogLine("getJson thread detached", verbose);
  }
}
