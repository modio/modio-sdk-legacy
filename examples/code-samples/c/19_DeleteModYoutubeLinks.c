#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onDeleteModYoutubeLinks(void *object, ModioResponse response)
{
  bool *wait = object;
  printf("Delete mod youtube links response: %i\n", response.code);
  if (response.code == 201)
  {
    printf("Youtube links deleted successfully!\n");
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

  char const *youtube_links_array[1];
  youtube_links_array[0] = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";

  printf("Getting mod...\n");
  modioDeleteModYoutubeLinks(&wait, mod_id, youtube_links_array, 1, &onDeleteModYoutubeLinks);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
