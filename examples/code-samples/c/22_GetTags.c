#include "modio_c.h"

void onGetModTags(void *object, ModioResponse response, ModioTag *tags_array, u32 tags_array_size)
{
  bool *wait = object;
  printf("Get Tags response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Listing tags:\n");
    for (u32 i = 0; i < tags_array_size; i++)
    {
      printf("%s\n", tags_array[i].name);
    }
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

  printf("Getting tags...\n");
  // We request the list of tags by providing the Mod's id
  modioGetModTags(&wait, mod_id, &onGetModTags);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
