#include "ModworksSDK.h"

void getJsonCallback(json j)
{
  cout<<endl<<"Mod names"<<endl;
  for(int i=0;i<(int)j["data"].size();i++)
  {
    cout<<j["data"][i]["name"]<<endl;
  }
}

int main(void)
{
  ModworksSDK modworks(/*game_id*/7, /*username*/"turupawn");

  modworks.getMods(&getJsonCallback);
  return 0;
}
