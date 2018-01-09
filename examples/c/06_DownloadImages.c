#include "modio_c.h"

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

void onModGet(void* object, ModioResponse response, ModioMod mod)
{
  bool* wait = object;
  printf("On mod get response: %i\n",response.code);
  if(response.code == 200)
  {
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
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Getting mod...\n");
  modioGetMod(&wait, mod_id, &onModGet);

  while(wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
