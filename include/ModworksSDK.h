#include "CurlWrapper.h"

class ModworksSDK
{
public:
  string current_user;
  int game_id;

  ModworksSDK(int game_id, string current_user);
  vector<string> getMods();
};
