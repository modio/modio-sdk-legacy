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

void onModGet(void* object, ModioResponse response, ModioMod mod)
{
  ContextObject* context_object = object;
  bool* wait = &(context_object->wait);
  printf("On mod get response: %i\n",response.code);
  if(mod.modfile.id == 0)
  {
    printf("Please select a mod containing a modfile\n");
    *wait = false;
    return;
  }
  if(response.code == 200)
  {
    printf("Id:\t%i\n",mod.id);
    printf("Name:\t%s\n",mod.name);
    printf("Modfile id:\t%i\n",mod.modfile.id);

    printf("Installing modfile...\n");

    char modfile_id_str[10];
    sprintf(modfile_id_str, "%d", mod.modfile.id);

    char instalation_path[100];
    strcpy(instalation_path, "");
    strcat(instalation_path, "../mods_dir/modfile_");
    strcat(instalation_path, modfile_id_str);

    context_object->modfile_id = mod.modfile.id;

    // Now we provide the Modfile id and the local path where the modfile will be installed
    modioInstallModfile(wait, mod.modfile.id, mod.modfile.download_url, (char*)instalation_path, &onModfileInstalled);
  }else
  {
    *wait = false;
  }
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  ContextObject context_object;
  context_object.wait = true;
  context_object.modfile_id = -1;

  // Let's start by requesting a single mod
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Getting mod...\n");
  modioGetMod(&context_object.wait, mod_id, &onModGet);

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
