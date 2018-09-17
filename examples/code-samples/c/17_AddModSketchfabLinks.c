#include "modio_c.h"

void onAddModSketchfabLinks(void *object, ModioResponse response)
{
  bool *wait = object;
  printf("Add mod sketchfab links response: %i\n", response.code);
  if (response.code == 201)
  {
    printf("Sketchfab links added successfully!\n");
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Let's start by requesting a single mod
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  char **sketchfab_links_array = (char **)malloc(1);
  sketchfab_links_array[0] = (char *)malloc(100);
  strcpy(sketchfab_links_array[0], "https://sketchfab.com/models/7793b895f27841f4930e6b71f75a8d74\0");

  printf("Getting mod...\n");
  modioAddModSketchfabLinks(&wait, mod_id, sketchfab_links_array, 1, &onAddModSketchfabLinks);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
