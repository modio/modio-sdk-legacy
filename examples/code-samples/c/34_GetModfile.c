#include "modio_c.h"

void onGetModfile(void *object, ModioResponse response, ModioModfile modfile)
{
  bool *wait = object;
  printf("On mod get response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Id:\t%i\n", modfile.id);
    printf("Version:\t%s\n", modfile.version);
    printf("Changelog:\t%s\n", modfile.changelog);
    printf("Metadata:\t%s\n", modfile.metadata_blob);
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // To retreive a single modfile we are going to need both the mod and modfile id
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Please enter the modfile id: \n");
  u32 modfile_id;
  scanf("%i", &modfile_id);

  printf("Getting modfile...\n");
  modioGetModfile(&wait, mod_id, modfile_id, &onGetModfile);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
