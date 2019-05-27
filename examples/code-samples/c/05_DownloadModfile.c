#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>
#include <stdlib.h>

bool wait = true;

void onDownloadMod(u32 response_code, u32 mod_id)
{
  printf("Download mod response: %i\n", response_code);
  if (response_code == 200)
  {
    printf("Mod downloaded successfully!\n");
    printf("Installing mods...\n");
    modioInstallDownloadedMods();
    printf("Finished installing mods\n");
  }
  wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

  // Let's start by requesting a single mod
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Downloading modfile...\n");

  // In order to know when a mod has been downloaded we can register a function as a listener
  modioSetDownloadListener(&onDownloadMod);
  // To download the mod we only have to provide it's id
  modioDownloadMod(mod_id);

  while (wait)
  {
    // While a mod is being downloaded, we can track it's progress by using the mod download queue related functions
    u32 queue_size = modioGetModDownloadQueueCount();
    if (queue_size != 0)
    {
      // The download queue contains all the information about the current downloads
			ModioQueuedModDownload *download_queue = malloc(queue_size * sizeof *download_queue);
      modioGetModDownloadQueue(download_queue);

      printf("\n");
      printf("Download queue:\n");
      printf("===============\n");

      for (u32 i = 0; i < queue_size; i++)
      {
        ModioQueuedModDownload *queued_mod_download = &(download_queue[i]);
        printf("Name: %s\n", queued_mod_download->mod.name);
        printf("Id: %d\n", queued_mod_download->mod.id);
        double current_progress = queued_mod_download->current_progress;
        double total_size = queued_mod_download->total_size;
        printf("Download progress: %f%%\n", (current_progress / total_size) * 100.0);
        printf("\n");
      }
      free(download_queue);
    }

    modioProcess();
    modioSleep(10);
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
