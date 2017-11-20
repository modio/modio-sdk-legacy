#include "ModIOSDK.h"
#include "Filter.h"

bool mods_get_finished = false;

void onModsGet(ModioResponse* response, ModioMod* mods, int mods_size)
{
  cout<<"On mod get response: "<<response->code<<endl;
  if(response->code == 200)
  {
    cout<<"Success!"<<endl;
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
  modioSetFilterLimit(filter,-1);
  modioSetFilterOffset(filter, -1);

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
