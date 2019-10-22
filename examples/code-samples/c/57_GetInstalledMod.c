#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, false, "e91c01b8882f4affeddd56c96111977b", NULL);

  // We request a single mod by providing it's id
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  // First, let's check if there is at least one mod installed
  ModioInstalledMod installed_mod;
  modioGetInstalledMod(mod_id, &installed_mod);
  if (installed_mod.mod_id != 0)
  {
    printf("Name: %s.\n", installed_mod.mod.name);
    printf("Path: %s.\n", installed_mod.path);
  }
  else
  {
    printf("That mod is currently not installed.\n");
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}