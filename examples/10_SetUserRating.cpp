#include "ModIOSDK.h"
#include "Filter.h"

int global_mod_id = -1;
bool mods_get_finished = false;
bool set_user_mod_vote_finished = false;

void onSetUserModVote(ModioResponse* response, int mod_id)
{
  cout<<"On user vote response: "<<response->code<<endl;
  if(response->code == 201)
  {
    cout<<"Vote successfully set"<<endl;
  }else
  {
    cout<<response->error->message<<endl;
  }
  set_user_mod_vote_finished = true;
}

void onModsGet(ModioResponse* response, ModioMod* mods, int mods_size)
{
  cout<<"On mod get response: "<<response->code<<endl;
  if(response->code == 200)
  {
    cout<<"Listing mods"<<endl;
    cout<<"============"<<endl;
    for(int i=0;i<(int)mods_size;i++)
    {
      cout<<"Mod["<<i<<"]"<<endl;
      cout<<"Id: \t"<<mods[i].id<<endl;
      cout<<"Name:\t"<<mods[i].name<<endl;
      global_mod_id = mods[i].id;
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

  cout<<"Setting vote..."<<endl;
  modioSetUserModVote(global_mod_id, true, &onSetUserModVote);

  while(!set_user_mod_vote_finished)
  {
    modioProcess();
  }

  modioShutdown();

  cout<<"Process finished"<<endl;

  return 0;
}
