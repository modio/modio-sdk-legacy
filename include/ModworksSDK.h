#ifndef MODWORKS_SDK_H
#define MODWORKS_SDK_H

#include "CurlWrapper.h"
#include "MinizipWrapper.h"
#include "Mod.h"

namespace modworks
{
  class SDK
  {
  public:
    string current_user;
    int game_id;

    SDK(int game_id, string current_user);
    void getMods(function< void(vector<Mod*>) > callback);
  };
}

#endif
