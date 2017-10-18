#include "ModIOSDK.h"
#include "Filter.h"

#ifdef _WIN32
#define WINDOWS
#endif
#ifdef _WIN64
#define WINDOWS
#endif

bool mods_get_finished = false;

void onModsGet(int response_code, char* message, ModioMod* mods, int mods_size)
{
  cout<<"On mod get response: "<<response_code<<endl;
  if(response_code == 200)
  {
    cout<<"Listing mods"<<endl;
    cout<<"============"<<endl;
    for(int i=0;i<(int)mods_size;i++)
    {
      cout<<"Mod["<<i<<"]"<<endl;
      cout<<"Id: \t"<<mods[i].id<<endl;
      cout<<"Name:\t"<<mods[i].name<<endl;
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

  modioShutdown();

  cout<<"Process finished"<<endl;

  return 0;
}
