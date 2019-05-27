#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onEditMod(void *object, ModioResponse response, ModioMod mod)
{
  bool *wait = object;
  printf("Edit mod response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Mod edited successfully!\n");
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

  // The Mod Editor helps setting up the fields that will be updated
  ModioModEditor mod_editor;
  modioInitModEditor(&mod_editor);
  modioSetModEditorName(&mod_editor, "Update Example");
  modioSetModEditorHomepageURL(&mod_editor, "http://www.updated.com");
  modioSetModEditorSummary(&mod_editor, "Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples.");
  modioSetModEditorDescription(&mod_editor, "This mod description was updated via the SDK examples. This mod description was updated via the SDK examples.");
  modioSetModEditorMetadataBlob(&mod_editor, "Optional updated metadata");
  modioSetModEditorMaturityOption(&mod_editor, MODIO_MATURITY_ALCOHOL | MODIO_MATURITY_EXPLICIT);

  modioEditMod(&wait, mod_id, mod_editor, &onEditMod);

  modioFreeModEditor(&mod_editor);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
