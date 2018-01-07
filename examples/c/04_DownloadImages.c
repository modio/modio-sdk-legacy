#include "schemas.h"

void onImageDownloaded(void* object, ModioResponse response)
{
  bool* wait = object;
  printf("Download Image response: %i\n", response.code);
  if(response.code == 200)
  {
    printf("Image downloaded successfully!\n");
  }
  *wait = false;
}

void onModsGet(void* object, ModioResponse response, ModioMod* mods, u32 mods_size)
{
  bool* wait = object;
  printf("On mod get response: %i\n",response.code);
  if(response.code == 200 && mods_size > 0)
  {
    ModioMod mod = mods[0];
    printf("Id:\t%i\n",mod.id);
    printf("Name:\t%s\n",mod.name);

    printf("Downloading log image...\n");

    // Now let's download the original logo full size to the selected path
    // Remember, you can also download other images such as headers and media images in different file sizes using the thumbnail fields
    modioDownloadImage(wait, mod.logo.original, (char*)"../mods_dir/full.png", &onImageDownloaded);
  }else
  {
    *wait = false;
  }
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  bool wait = true;

  // Let's start by requesting a single mod

  ModioFilterCreator filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter,1);

  printf("Getting mods...\n");
  modioGetMods(&wait, filter, &onModsGet);

  while(wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
