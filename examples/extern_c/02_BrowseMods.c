#include "schemas.h"

bool mods_get_finished = false;

void onModsGet(void* object, ModioResponse response, ModioMod* mods, int mods_size)
{
  printf("On mod get response: %i\n",response.code);
  if(response.code == 200)
  {
    printf("Listing mod\n");
    printf("============\n");
    for(int i=0;i<(int)mods_size;i++)
    {
      printf("Mod[%i]\n",i);
      printf("Id: %i\n",mods[i].id);
      printf("Name: %s\n",mods[i].name);
    }

    printf("\nCursor data:\n");
    printf("Cursor id: %i\n",response.cursor_id);
    printf("Prev id: %i\n",response.prev_id);
    printf("Next id: %i\n",response.next_id);
    printf("Result count: %i\n",response.result_count);
  }

  mods_get_finished = true;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  ModioFilterHandler filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter,3);
  modioAddFilterLikeField(&filter, (char*)"name", (char*)"Example Mod");
  modioAddFilterLikeField(&filter, (char*)"description", (char*)"This mod description was added via the SDK examples. This mod description was added via the SDK examples.");

  printf("Getting mods...\n");
  modioGetMods(NULL,&filter, &onModsGet);

  while(!mods_get_finished)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
