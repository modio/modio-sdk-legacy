#include "ModIOSDK.h"

bool mods_get_finished = false;
int mods_to_download = -1;
int mods_downloaded = 0;

void onModDeleted(ModioResponse* response, ModioMod* mod)
{
  cout<<"Mod Delete response: "<<response->code<<endl;
  if(response->code == 204)
  {
    cout<<"Mod deleted downloaded successfully!"<<endl;
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
      cout<<"Deleting mod..."<<endl;

      modioDeleteMod(&(mods[i]), &onModDeleted);
    }
    mods_to_download = mods_size;
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

  while(!mods_get_finished);

  while(mods_downloaded < mods_to_download);

  modioShutdown();

  cout<<"Process finished"<<endl;

  return 0;
}
