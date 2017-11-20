#include "ModIOSDK.h"
#include "Filter.h"

bool mods_get_finished = false;

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
    }

    cout<<endl;
    cout<<"Cursor data:"<<endl;
    cout<<"Cursor id: "<<response->cursor_id<<endl;
    cout<<"Prev id: "<<response->prev_id<<endl;
    cout<<"Next id: "<<response->next_id<<endl;
    cout<<"Result count: "<<response->result_count<<endl;
  }

  mods_get_finished = true;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  ModioFilter* filter = new ModioFilter;
  modioInitFilter(filter);
  modioSetFilterLimit(filter,3);
  modioAddFilterLikeField(filter, (char*)"name", (char*)"Example Mod");
  modioAddFilterLikeField(filter, (char*)"description", (char*)"This mod description was added via the SDK examples. This mod description was added via the SDK examples.");

  cout<<"Getting mods..."<<endl;
  modioGetMods(filter, &onModsGet);

  while(!mods_get_finished)
  {
    modioProcess();
  }

  modioShutdown();

  cout<<"Process finished"<<endl;

  return 0;
}
