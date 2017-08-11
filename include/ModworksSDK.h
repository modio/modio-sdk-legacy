#ifndef MODWORKSSDK_H
#define MODWORKSSDK_H

#include "CurlWrapper.h"
#include "Mod.h"

class ModworksSDK
{
public:
  string current_user;
  int game_id;

  ModworksSDK(int game_id, string current_user);
  void getMods(function< void(vector<Mod*>) > callback);
};

#endif
