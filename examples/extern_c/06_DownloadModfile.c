#include "schemas.h"

bool mods_get_finished = false;
bool modfile_installed = false;

ModioModfile* global_modfile = NULL;

void onModfileInstalled(void* object, ModioResponse response)
{
  printf("Install Mod response: %i\n", response.code);
  if(response.code == 200)
  {
    printf("Mod installed successfully!\n");
  }
  modfile_installed = true;
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
      global_modfile = &(mods[i].modfile);
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
  modioGetMods(NULL, filter, &onModsGet);

  while(!mods_get_finished)
  {
    modioProcess();
  }

  printf("Installing modfile...\n");

  char modfile_id_str[10];
  sprintf(modfile_id_str, "%d", global_modfile->id);

  char instalation_path[100];
  strcpy(instalation_path, "");
  strcat(instalation_path, "mods_dir/modfile_");
  strcat(instalation_path, modfile_id_str);

  modioInstallModfile(NULL, global_modfile->id, global_modfile->download_url, (char*)instalation_path, &onModfileInstalled);

  while(!modfile_installed)
  {
    if(modioGetModfileState(global_modfile->id) == MODIO_MODFILE_INSTALLING)
    {
      double modfile_download_progress = modioGetModfileDownloadPercentage(global_modfile->id);
      if(modfile_download_progress != 0)
        printf("Download progress: %f%%\n", modfile_download_progress);
    }
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
