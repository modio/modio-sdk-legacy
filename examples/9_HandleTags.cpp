#include "ModIOSDK.h"
#include "exported_methods/TagMethods.h"

bool mod_get_finished = false;
bool tags_get_finished = false;
bool tags_add_finished = false;
bool tags_delete_finished = false;

ModioMod* global_mod = NULL;

void onTagsGet(ModioResponse* response, int mod_id, ModioTag* tags_array, int tags_array_size)
{
  cout<<"Get tags response: "<<response->code<<endl;
  if(response->code == 200)
  {
    cout<<"Listing tags:"<<endl;
    for(int i=0; i<tags_array_size; i++)
    {
      cout<<tags_array[i].tag<<endl;
    }
  }
  tags_get_finished = true;
}

void onTagsAdded(ModioResponse* response, int mod_id, ModioTag* tags_array, int tags_array_size)
{
  cout<<"Add tags response: "<<response->code<<endl;
  if(response->code == 201)
  {
    cout<<"Tags added!"<<endl;
  }
  tags_add_finished = true;
}

void onTagsDeleted(ModioResponse* response, int mod_id, ModioTag* tags_array, int tags_array_size)
{
  cout<<"Delete tags response: "<<response->code<<endl;
  if(response->code == 204)
  {
    cout<<"Tags deleted!"<<endl;
  }
  tags_delete_finished = true;
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
      global_mod = &(mods[i]);
      cout<<"Mod["<<i<<"]"<<endl;
      cout<<"Id: \t"<<mods[i].id<<endl;
      cout<<"Name:\t"<<mods[i].name<<endl;
    }
  }
  mod_get_finished = true;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  ModioFilter* filter = new ModioFilter;
  modioInitFilter(filter);
  modioSetFilterLimit(filter,1);

  cout<<"Getting mods..."<<endl;
  modioGetMods(filter, &onModsGet);

  while(!mod_get_finished);

  cout<<"Getting mod tags"<<endl;
  modioGetTags(global_mod->id, &onTagsGet);

  while(!tags_get_finished);

  cout<<"Adding tag..."<<endl;

  char** tags_array = new char*[1];
  tags_array[0] = new char[50];
  strcpy(tags_array[0],"Hard");
  int tags_array_size = 1;
  modioAddTags(global_mod->id, tags_array, tags_array_size, &onTagsAdded);

  while(!tags_add_finished);

  cout<<"Getting mod tags"<<endl;
  modioGetTags(global_mod->id, &onTagsGet);

  tags_get_finished = false;
  while(!tags_get_finished);

  cout<<"Deleting tag..."<<endl;

  modioDeleteTags(global_mod->id, tags_array, tags_array_size, &onTagsDeleted);
  while(!tags_delete_finished);

  cout<<"Getting mod tags"<<endl;
  modioGetTags(global_mod->id, &onTagsGet);

  tags_get_finished = false;
  while(!tags_get_finished);

  modioShutdown();

  cout<<"Process finished"<<endl;

  return 0;
}
