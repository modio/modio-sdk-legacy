#include "ModIOSDK.h"
#include "Filter.h"

int global_mod_id = -1;
bool mods_get_finished = false;
bool subscribed_finished = false;
bool unsubscribed_finished = false;

void onSubscribed(ModioResponse* response, int mod_id)
{
  cout<<"On subscribed response: "<<response->code<<endl;
  if(response->code == 201)
  {
    cout<<"Subscribed successfully"<<endl;
  }
  subscribed_finished = true;
}

void onUnsubscribed(ModioResponse* response, int mod_id)
{
  cout<<"On unsubscribed response: "<<response->code<<endl;
  if(response->code == 204)
  {
    cout<<"Unsubscribed successfully"<<endl;
  }
  unsubscribed_finished = true;
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

  cout<<"Subscribing..."<<endl;
  modioSubscribeMod(global_mod_id, &onSubscribed);

  while(!subscribed_finished)
  {
    modioProcess();
  }

  cout<<"Unsubscribing..."<<endl;
  modioUnsubscribeMod(global_mod_id, &onUnsubscribed);

  while(!unsubscribed_finished)
  {
    modioProcess();
  }

  modioShutdown();

  cout<<"Process finished"<<endl;

  return 0;
}
