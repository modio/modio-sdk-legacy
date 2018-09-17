#include "modio_c.h"

void onDeleteModImages(void *object, ModioResponse response)
{
  bool *wait = object;
  printf("Delete mod images response: %i\n", response.code);
  if (response.code == 201)
  {
    printf("Images deleted successfully!\n");
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

  char **images_array = (char **)malloc(1);
  images_array[0] = (char *)malloc(100);
  strcpy(images_array[0], "example.png\0");

  printf("Getting mod...\n");
  modioDeleteModImages(&wait, mod_id, images_array, 1, &onDeleteModImages);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
