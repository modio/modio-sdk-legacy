#include "ModIOSDK.h"

bool mods_get_finished = false;
int mods_to_download = -1;
int mods_downloaded = 0;

void onModEdited(ModioResponse* response, ModioMod* mod)
{
  cout<<"Mod Edit response: "<<response->code<<endl;
  if(response->code == 200)
  {
    cout<<"Mod edited successfully!"<<endl;
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
      cout<<"Editing mod..."<<endl;

      ModioModHandler* mod_handler = new ModioModHandler;
      modioInitModHandler(mod_handler);
      //Required fields
      modioSetLogoPath(mod_handler, (char*)"ModExample/logo.png");
      modioSetName(mod_handler, (char*)"Update Example");
      modioSetHomepage(mod_handler, (char*)"http://www.updated.com");
      modioSetSummary(mod_handler, (char*)"Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples.");
      modioAddTag(mod_handler, (char*)"Easy");
      //Optional fields
      modioSetPrice(mod_handler, 2.99);
      //setStock(mod_handler, 50);//The developer should allow mods to control mod supply and scarcity
      modioSetDescription(mod_handler, (char*)"This mod description was updated via the SDK examples. This mod description was updated via the SDK examples.");
      modioSetMetadata(mod_handler, (char*)"Optional updated metadata");
      //setNameid(mod_handler, "my-example-mod"); //Name id must be unique
      //setModfile(mod_handler, int modfile); //Modfile should exist

      modioEditMod(mods[i].id, mod_handler, &onModEdited);
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

  while(!mods_get_finished)
  {
    modioProcess();
  }

  while(mods_downloaded < mods_to_download)
  {
    modioProcess();
  }

  modioShutdown();

  cout<<"Process finished"<<endl;

  return 0;
}
