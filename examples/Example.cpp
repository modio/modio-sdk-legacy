#include "ModworksSDK.h"

int main(void)
{
  ModworksSDK modworks(/*game_id*/7, /*username*/"turupawn");

  vector<string> mod_names = modworks.getMods();
  cout<<endl<<"Mod names:"<<endl;
  for(int i=0;i<(int)mod_names.size();i++)
  {
    cout<<mod_names[i]<<endl;
  }

  return 0;
}
