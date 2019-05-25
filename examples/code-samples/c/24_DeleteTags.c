#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onDeleteModTags(void *object, ModioResponse response)
{
  bool *wait = object;
  printf("Delete tags response: %i\n", response.code);
  if (response.code == 201)
  {
    printf("Tags deleted successfully!\n");
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Let's start by requesting a single mod
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Adding tags...\n");

  char const *tags_array[1];
  tags_array[0] = "Hard";

  // We delete tags by providing the selected Mod id and the tag names
  modioDeleteModTags(&wait, mod_id, (char const* const*)tags_array, 1, &onDeleteModTags);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
