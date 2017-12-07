#include "schemas.h"

ModioMod* global_mod;

bool mods_get_finished = false;
bool images_downloaded = false;

void onImageDownloaded(void* object, ModioResponse response, char* path)
{
  printf("Download Image response: %i\n", response.code);
  if(response.code == 200)
  {
    printf("Image downloaded successfully!\n");
  }
  images_downloaded = true;
}

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
      printf("Id:\t%i\n",mods[i].id);
      printf("Name:\t%s\n",mods[i].name);
      global_mod = &(mods[i]);
    }
  }
  mods_get_finished = true;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  ModioFilterHandler filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter,1);

  printf("Getting mods...\n");
  modioGetMods(NULL, &filter, &onModsGet);

  while(!mods_get_finished)
  {
    modioProcess();
  }

  printf("Downloading log image...\n");
  modioDownloadImage(NULL, global_mod->logo.original, (char*)"mods_dir/full.png", &onImageDownloaded);

  while(!images_downloaded)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
