#include "ModIOSDK.h"

bool mods_get_finished = false;
int mods_to_download = -1;
int mods_downloaded = 0;

void onModEdited(ModioResponse* response, ModioMod* mod)
{
  cout<<"Mod Edit response: "<<response->code<<endl;
  if(response->code == 200)
  {
    cout<<"Mod edited downloaded successfully!"<<endl;
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

      ModHandler* mod_handler = new ModHandler;
      //Required fields
      setLogoPath(mod_handler, "ModExample/logo.png");
      setName(mod_handler, "Update Example");
      setHomepage(mod_handler, "http://www.updated.com");
      setSummary(mod_handler, "Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples.");
      addTag(mod_handler, "Easy");
      //Optional fields
      setPrice(mod_handler, 2.99);
      //setStock(mod_handler, 50);//The developer should allow mods to control mod supply and scarcity
      setDescription(mod_handler, "This mod description was updated via the SDK examples. This mod description was updated via the SDK examples.");
      setMetadata(mod_handler, "Optional updated metadata");
      //setNameid(mod_handler, "my-example-mod"); //Name id must be unique
      //setModfile(mod_handler, int modfile); //Modfile should exist

      modioEditMod(&(mods[i]), mod_handler, &onModEdited);
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
