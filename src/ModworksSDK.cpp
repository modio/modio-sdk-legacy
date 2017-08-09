#include "ModworksSDK.h"

ModworksSDK::ModworksSDK(int game_id, string current_user)
{
  this->game_id = game_id;
  this->current_user = current_user;
}

void orales(json j)
{

}

void ModworksSDK::getMods(function< void(json) > callback)
{
  vector<string> headers;
  headers.push_back(string("Authorization: Bearer ") + current_user);
  string url = string("https://api.mod.works/v1/games/") + toString(game_id) + "/mods";
  getJson(url, headers, callback);
}
