#include "ModworksSDK.h"

void downloadLogoThumbnailCallback(int result)
{
  if(result == 1)
  {
    cout<<"Download successful"<<endl;
  }
}

void getJsonCallback(vector<Mod*> mods)
{
  cout<<endl<<"Listing mods:"<<endl;
  for(int i=0;i<(int)mods.size();i++)
  {
    cout<<mods[i]->name<<endl;
    cout<<mods[i]->summary<<endl;
    mods[i]->downloadLogoThumbnail(&downloadLogoThumbnailCallback);
  }
}

int main(void)
{
  ModworksSDK modworks(/*game_id*/7, /*username*/"turupawn");

  modworks.getMods(&getJsonCallback);

  return 0;
}
