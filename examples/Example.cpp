#include "ModworksSDK.h"

int files_downloaded = 0;
int files_to_download = 4;

void downloadLogoThumbnailCallback(int result,  Mod* mod, string path)
{
  if(result == 1)
  {
    cout<<mod->name<<" download thumb successful at "<<path<<endl;
  }
  files_downloaded++;
}

void downloadModFileCallback(int result,  Mod* mod, string path)
{
  if(result == 1)
  {
    cout<<mod->name<<" download file successful at "<<path<<endl;
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
    mods[i]->download(&downloadModFileCallback);
  }
}

int main(void)
{
  ModworksSDK modworks(/*game_id*/7, /*username*/"turupawn");

  modworks.getMods(&getJsonCallback);

  cout<<"Downloading"<<endl;
  while(files_downloaded<files_to_download);
  cout<<"Finshed"<<endl;

  return 0;
}
