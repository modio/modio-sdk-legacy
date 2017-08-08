#include "ModworksSDK.h"

int main(void)
{
  json j = getJson("https://api.mod.works/v1/games/7/mods");

  for(int i=0;i<(int)j["data"].size();i++)
  {
    cout<<j["data"][i]["name"]<<endl;
  }

  return 0;
}
