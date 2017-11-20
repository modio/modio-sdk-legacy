#include "ModIOSDK.h"

ModioMod* global_mod;

bool mods_get_finished = false;
int images_downloaded = 0;
bool mod_logo_edited = false;

void onImageDownloaded(ModioResponse* response, char* path)
{
  cout<<"Download Image response: "<<response->code<<endl;
  if(response->code == 200)
  {
    cout<<"Image downloaded successfully!"<<endl;
  }
  images_downloaded++;
}

void onModLogoEdited(ModioResponse* response, int mod_id)
{
  cout<<"Edit mod logo response: "<<response->code<<endl;
  if(response->code == 200)
  {
    cout<<"Mod logo edited successfully!"<<endl;
  }
  mod_logo_edited = true;
}

void onModsGet(ModioResponse* response, ModioMod* mods, int mods_size)
{
  cout<<"GetMods response: "<<response->code<<endl;
  if(response->code == 200)
  {
    cout<<"Listing mods"<<endl;
    cout<<"============"<<endl;
    for(int i=0;i<(int)mods_size;i++)
    {
      cout<<"Mod["<<i<<"]"<<endl;
      cout<<"Id: \t"<<mods[i].id<<endl;
      cout<<"Name:\t"<<mods[i].name<<endl;

      global_mod = &(mods[i]);
    }
  }

  mods_get_finished = true;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  ModioFilter* filter = new ModioFilter;
  modioInitFilter(filter);
  modioSetFilterLimit(filter,1);

  cout<<"Getting mods..."<<endl;
  modioGetMods(filter, &onModsGet);

  while(!mods_get_finished)
  {
    modioProcess();
  }

  cout<<"Editing mod logo..."<<endl;
  modioEditModLogo(global_mod->id, (char*)"ModExample/logo.png", &onModLogoEdited);

  while(!mod_logo_edited)
  {
    modioProcess();
  }

  cout<<"Downloading logo image..."<<endl;
  modioDownloadImage(global_mod->logo->full, (char*)"mods_dir/full.png", &onImageDownloaded);
  modioDownloadImage(global_mod->logo->thumb_1280x720, (char*)"mods_dir/thumb_1280x720.png", &onImageDownloaded);
  modioDownloadImage(global_mod->logo->thumb_640x360, (char*)"mods_dir/thumb_640x360.png", &onImageDownloaded);
  modioDownloadImage(global_mod->logo->thumb_320x180, (char*)"mods_dir/thumb_320x180.png", &onImageDownloaded);

  while(images_downloaded<4)
  {
    modioProcess();
  }

  modioShutdown();

  cout<<"Process finished"<<endl;

  return 0;
}
