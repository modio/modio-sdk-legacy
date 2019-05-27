#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onDeleteModComment(void *object, ModioResponse response)
{
  bool *wait = object;
  printf("On delete mod comment response: %i\n", response.code);
  if (response.code == 204)
  {
    printf("Success\n");
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

  printf("Please enter the comment id: \n");
  u32 comment_id;
  scanf("%i", &comment_id);

  printf("Getting comments...\n");

  // Now we finished setting up the filters we are ready to request the mods
  modioDeleteModComment(&wait, mod_id, comment_id, &onDeleteModComment);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
