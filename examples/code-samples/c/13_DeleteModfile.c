#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onDeleteModfile(void *object, ModioResponse response)
{
  bool *wait = object;
  printf("Delete modfile response: %i\n", response.code);
  if (response.code == 204)
  {
    printf("Modfile deleted successfully!\n");
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // In order to delete a modfile you will need the mod and modfile id
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Please enter the modfile id: \n");
  u32 modfile_id;
  scanf("%i", &modfile_id);

  printf("Deleting modfile...\n");
  modioDeleteModfile(&wait, mod_id, modfile_id, &onDeleteModfile);


  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
