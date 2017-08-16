#include "ModworksSDK.h"

ModworksSDK::ModworksSDK(int game_id, string current_user)
{
  this->game_id = game_id;
  this->current_user = current_user;

  zipper::CDirEntry::createDir(".modworks");
  zipper::CDirEntry::createDir(".modworks/images");
  zipper::CDirEntry::createDir(".modworks/tmp");
}

void ModworksSDK::getMods(function< void(vector<Mod*>) > callback)
{
  vector<string> headers;
  headers.push_back(string("Authorization: Bearer ") + current_user);
  string url = string("https://api.mod.works/v1/games/") + toString(game_id) + "/mods";

  std::thread get_json_thread(getJson, url, headers, callback);
  get_json_thread.detach();
}
