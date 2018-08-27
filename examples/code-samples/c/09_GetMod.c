#include "modio_c.h"

void onGetMod(void *object, ModioResponse response, ModioMod mod)
{
  bool *wait = object;
  printf("On mod get response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Id: %i\n", mod.id);
    printf("Name: %s\n", mod.name);
    printf("Homapage url: %s\n", mod.homepage_url);
    printf("Summary: %s\n", mod.summary);
    printf("Tags:\n");
    for (int i = 0; i < mod.tags_array_size; i++)
      printf("* %s\n", mod.tags_array[i].name);
    printf("Description: %s\n", mod.description);
    printf("Description (plain text): %s\n", mod.description_plaintext);
    printf("Metadata blob: %s\n", mod.metadata_blob);
    printf("Visible: %i\n", mod.visible);
    printf("Maturity option: %i\n", mod.maturity_option);
    printf("Logo url: %s\n", mod.logo.original);
    printf("Date added: %i\n", mod.date_added);
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // We request a single mod by providing it's id
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Getting mod...\n");
  modioGetMod(&wait, mod_id, &onGetMod);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
