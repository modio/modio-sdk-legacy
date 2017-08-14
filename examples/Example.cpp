#include "ModworksSDK.h"

int files_downloaded = 0;

void downloadLogoThumbnailCallback(int result,  Mod* mod)
{
  if(result == 1)
  {
    cout<<"Download successful"<<endl;
    cout<<mod->logo_thumbnail_path<<endl;
  }
  files_downloaded++;
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

  cout<<"Downloading"<<endl;
  while(files_downloaded<2);
  cout<<"Finshed"<<endl;

  return 0;
}
