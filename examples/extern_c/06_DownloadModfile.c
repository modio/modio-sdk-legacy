#include "schemas.h"

typedef struct
{
  bool wait;
  int modfile_id;
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

void onModsGet(void* object, ModioResponse response, ModioMod* mods, int mods_size)
{
  ContextObject* context_object = object;
  bool* wait = &(context_object->wait);
  printf("On mod get response: %i\n",response.code);
  if(response.code == 200 && mods_size > 0)
  {
    ModioMod mod = mods[0];
    printf("Id:\t%i\n",mod.id);
    printf("Name:\t%s\n",mod.name);
    printf("Modfile id:\t%i\n",mod.modfile.id);

    printf("Installing modfile...\n");

    char modfile_id_str[10];
    sprintf(modfile_id_str, "%d", mod.modfile.id);

    char instalation_path[100];
    strcpy(instalation_path, "");
    strcat(instalation_path, "mods_dir/modfile_");
    strcat(instalation_path, modfile_id_str);

    context_object->modfile_id = mod.modfile.id;
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

  ModioFilterHandler filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter,1);

  printf("Getting mods...\n");
  modioGetMods(&context_object, filter, &onModsGet);

  while(context_object.wait)
  {
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
