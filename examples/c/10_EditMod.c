#include "modio_c.h"

void onModEdited(void* object, ModioResponse response, ModioMod mod)
{
  bool* wait = object;
  printf("Mod Edit response: %i\n", response.code);
  if(response.code == 200)
  {
    printf("Mod edited successfully!\n");
  }
  *wait = false;
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  bool wait = true;

  // Let's start by requesting a single mod
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  // The Mod Editor helps setting up the fields that will be updated
  ModioModEditor mod_editor;
  modioInitModEditor(&mod_editor);
  modioSetModEditorName(&mod_editor, (char*)"Update Example Non admin");
  modioSetModEditorHomepage(&mod_editor, (char*)"http://www.updated.com");
  modioSetModEditorSummary(&mod_editor, (char*)"Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples.");
  modioSetModEditorDescription(&mod_editor, (char*)"This mod description was updated via the SDK examples. This mod description was updated via the SDK examples.");
  modioSetModEditorMetadataBlob(&mod_editor, (char*)"Optional updated metadata");

  modioEditMod(&wait, mod_id, mod_editor, &onModEdited);

  modioFreeModEditor(&mod_editor);

  while(wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
