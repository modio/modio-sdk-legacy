#include "modio_c.h"

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
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Let's start by requesting a single mod
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Adding tags...\n");

  char **tags_array = (char **)malloc(1);
  tags_array[0] = (char *)malloc(100);
  strcpy(tags_array[0], "Hard\0");

  // We delete tags by providing the selected Mod id and the tag names
  modioDeleteModTags(&wait, mod_id, (char **)tags_array, 1, &onDeleteModTags);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
