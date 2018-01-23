#include "modio_c.h"

typedef struct
{
  bool wait;
  u32 modfile_id;
}ContextObject;

void onModfileInstalled(void* object, ModioResponse response)
{
  bool* wait = object;
  printf("Install Mod response: %i\n", response.code);
  if(response.code == 200)
  {
    printf("Mod installed successfully!\n");
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char*)"e91c01b8882f4affeddd56c96111977b");

  ContextObject context_object;
  context_object.wait = true;
  context_object.modfile_id = -1;

  // Let's start by requesting a single mod
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Installing modfile...\n");

  char instalation_path[100];
  strcpy(instalation_path, "");
  strcat(instalation_path, "../mods_dir/modfile");

  // Now we provide the Modfile id and the local path where the modfile will be installed
  modioInstallMod(&context_object.wait, mod_id, (char*)instalation_path, &onModfileInstalled);

  while(context_object.wait)
  {
    // Track download progress by providing the modfile id
    if(modioGetModfileState(context_object.modfile_id) == MODIO_MODFILE_INSTALLING)
    {
      double modfile_download_progress = modioGetModfileDownloadPercentage(context_object.modfile_id);
      if(modfile_download_progress != 0)
        printf("Download progress: %f%%\n", modfile_download_progress);
    }
    modioProcess();
    modioSleep(10);
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
