#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, false, true, "e91c01b8882f4affeddd56c96111977b", NULL);

  // First, let's check if there is at least one mod installed
  u32 installed_mods_count = modioGetAllInstalledModsCount();
  if (installed_mods_count > 0)
  {
    // If that's the case, we retreive the information of all the mods installed
    ModioInstalledMod* installed_mods = malloc(sizeof(ModioInstalledMod) * installed_mods_count);
    modioGetAllInstalledMods(installed_mods);

    // Now we delete the local mod folder by providing it's id
    if (modioUninstallMod(installed_mods[0].mod.id))
    {
      printf("Mod uninstalled successfully.\n");
    }
    else
    {
      printf("Error uninstalling mod.\n");
    }
    free(installed_mods);
  }
  else
  {
    printf("There are no Mods installed, please try installing one before running this example again.\n");
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
