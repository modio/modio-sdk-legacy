#include "ModIOSDK.h"

bool add_mod_finished = false;
bool add_modfile_finished = true;

string modfile_path = "ModExample/modfile/";
string modfile_version = "v1.1.x";
string modfile_changelog = "This is a change log, this is a changelog , this is a changelog , this is a changelog , this is a changelog , this is a changelog, this is a changelog , this is a changelog , this is a changelog";

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

    ModioModfileHandler* modfile_handler = new ModioModfileHandler();
    modioInitModfileHandler(modfile_handler);
    //Required
    modioSetModfilePath(modfile_handler, (char*)modfile_path.c_str());
    modioSetModfileVersion(modfile_handler, (char*)modfile_version.c_str());
    modioSetModfileChangelog(modfile_handler, (char*)modfile_changelog.c_str());
    //Optional
    modioSetModfileActive(modfile_handler, true);

    add_modfile_finished = false;
    modioAddModfile(mod->id, modfile_handler, &onModfileAdded);
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

  ModioModHandler* mod_handler = new ModioModHandler;
  modioInitModHandler(mod_handler);
  //Required fields
  modioSetLogoPath(mod_handler, (char*)"ModExample/logo.png");
  modioSetName(mod_handler, (char*)"Example Mod Test30");
  modioSetHomepage(mod_handler, (char*)"http://www.webpage.com");
  modioSetSummary(mod_handler, (char*)"Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples.");
  modioAddTag(mod_handler, (char*)"Easy");
  modioAddTag(mod_handler, (char*)"Medium");
  //Optional fields
  modioSetPrice(mod_handler, 1.99);
  modioSetStock(mod_handler, 25);
  modioSetDescription(mod_handler, (char*)"This mod description was added via the SDK examples. This mod description was added via the SDK examples.");
  modioSetMetadata(mod_handler, (char*)"Optional metadata");
  //setNameid(mod_handler, "my-example-mod"); //Name id must be unique
  //setModfile(mod_handler, int modfile); //Modfile should exist

  modioAddMod(mod_handler, &onModAdded);

  while(!add_mod_finished);
  while(!add_modfile_finished);

  modioShutdown();

  cout<<"Process finished"<<endl;

  return 0;
}
