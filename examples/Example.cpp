#include "ModworksSDK.h"

int files_downloaded = 0;
int files_to_download = 4;
modworks::SDK* mworks;

void onThumbnailDownloaded(int result,  modworks::Mod* mod, string path)
{
  if(result == 1)
  {
    cout<<mod->name<<" download thumb successful at "<<path<<endl;
  }
  files_downloaded++;
}

void onModInstalled(int result,  modworks::Mod* mod, string path)
{
  if(result == 1)
  {
    cout<<mod->name<<" download file successful at "<<path<<endl;
  }
  files_downloaded++;
}

void onModsGet(vector<modworks::Mod*> mods)
{
  cout<<endl<<"Listing mods:"<<endl;
  for(int i=0;i<(int)mods.size();i++)
  {
    cout<<mods[i]->name<<endl;
    cout<<mods[i]->summary<<endl;
    mods[i]->downloadLogoThumbnail(&onThumbnailDownloaded);
    mods[i]->download("mod_directory",&onModInstalled);
  }
}


int main(void)
{
  //modworks::compress("dir/path","out.zip");

  mworks = new modworks::SDK(/*game_id*/7, /*username*/"turupawn");
  mworks->getMods(&onModsGet);
  while(files_downloaded<files_to_download);

  return 0;
}
