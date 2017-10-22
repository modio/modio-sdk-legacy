#include "ModIOSDK.h"

bool add_mod_finished = false;
bool add_modfile_finished = true;

void onModfileAdded(ModioResponse* response, ModioModfile* modfile)
{
  cout<<"Add Modfile Response: "<<response->code<<endl;
  if(response->code == 201)
  {
    cout<<"Modfile added!"<<endl;
    cout<<"Modfile id: "<<modfile->id<<endl;
  }
  add_modfile_finished = true;
}

void onModAdded(ModioResponse* response, ModioMod* mod)
{
  cout<<"Add Mod Response code: "<<response->code<<endl;

  if(response->code == 201)
  {
    cout<<"Mod added!"<<endl;
    cout<<"Mod id: "<<mod->id<<endl;

    ModfileHandler* modfile_handler = new ModfileHandler();
    //Required
    setModfilePath(modfile_handler, "ModExample/modfile/");
    setModfileVersion(modfile_handler, "v1.1.1");
    setModfileChangelog(modfile_handler, "This is a change log, this is a changelog , this is a changelog , this is a changelog , this is a changelog , this is a changelog, this is a changelog , this is a changelog , this is a changelog");
    //Optional
    setModfileActive(modfile_handler, true);

    add_modfile_finished = false;
    modioAddModfile(mod, modfile_handler, &onModfileAdded);
  }

  add_mod_finished = true;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  if(!modioIsLoggedIn())
  {
    cout<<"You are not logged in, please login before creating a mod."<<endl;
    return 0;
  }

  ModHandler* mod_handler = new ModHandler;
  //Required fields
  setLogoPath(mod_handler, "ModExample/logo.png");
  setName(mod_handler, "Example Mod");
  setHomepage(mod_handler, "http://www.webpage.com");
  setSummary(mod_handler, "Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples.");
  addTag(mod_handler, "Easy");
  addTag(mod_handler, "Medium");
  //Optional fields
  setPrice(mod_handler, 1.99);
  setStock(mod_handler, 25);
  setDescription(mod_handler, "This mod description was added via the SDK examples. This mod description was added via the SDK examples.");
  setMetadata(mod_handler, "Optional metadata");
  //setNameid(mod_handler, "my-example-mod"); //Name id must be unique
  //setModfile(mod_handler, int modfile); //Modfile should exist

  modioAddMod(mod_handler, &onModAdded);

  while(!add_mod_finished);
  while(!add_modfile_finished);

  modioShutdown();

  cout<<"Process finished"<<endl;

  return 0;
}
