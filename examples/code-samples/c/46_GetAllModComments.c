#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onGetAllModComments(void *object, ModioResponse response, ModioComment comments[], u32 comments_size)
{
  bool *wait = object;
  printf("On get all mod comments response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Listing comments\n");
    printf("================\n");
    for (u32 i = 0; i < comments_size; i++)
    {
    printf("Id:\t\t%i\n", comments[i].id);
    printf("Mod id:\t\t%i\n", comments[i].mod_id);
    printf("Date added:\t%i\n", comments[i].date_added);
    printf("Reply id:\t%i\n", comments[i].reply_id);
    printf("Thread position:%s\n", comments[i].thread_position);
    printf("Karma:\t\t%i\n", comments[i].karma);
    printf("Karma guest:\t%i\n", comments[i].karma_guest);
    printf("Content:\t%s\n", comments[i].content);
    printf("User:\t\t%s\n", comments[i].user.username);
    printf("\n");
    }
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Before requesting mods, let's define the query filters
  ModioFilterCreator filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter, 3);

  // Let's start by requesting a single mod
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Getting comments...\n");

  // Now we finished setting up the filters we are ready to request the mods
  modioGetAllModComments(&wait, mod_id, filter, &onGetAllModComments);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}