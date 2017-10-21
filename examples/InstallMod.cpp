#include "ModIOSDK.h"

bool mods_get_finished = false;
int mods_to_download = -1;
int mods_downloaded = 0;

void onModInstalled(ModioResponse* response, char* path)
{
  cout<<"InstallMod response: "<<response->code<<endl;
  if(response->code == 200)
  {
    cout<<"Mod installed successfully!"<<endl;
  }
  mods_downloaded++;
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
      cout<<"Installing..."<<endl;
      string instalation_path_str = string("mods_dir/") + mods[i].name + "_" + modio::toString(mods[i].id);
      char* instalation_path = new char[instalation_path_str.size() + 1];
      strcpy(instalation_path, instalation_path_str.c_str());
      modioInstallMod(&(mods[i]), instalation_path, &onModInstalled);
    }
    mods_to_download = mods_size;
  }else
  {
    cout<<"Error message: "<<response->error->message<<endl;
    if(response->error->errors_array_size > 0)
    {
      cout<<"Errors:"<<endl;
      for(int i=0; i<response->error->errors_array_size; i++)
      {
        cout<<response->error->errors_array[i]<<endl;
      }
    }
  }

  mods_get_finished = true;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  ModioFilter* filter = new ModioFilter;
  modioInitFilter(filter);
  modioSetFilterLimit(filter,3);

  cout<<"Getting mods..."<<endl;
  modioGetMods(filter, &onModsGet);

  while(!mods_get_finished);

  while(mods_downloaded < mods_to_download);

  modioShutdown();

  cout<<"Process finished"<<endl;

  return 0;
}
