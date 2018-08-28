#include "modio_c.h"

void onEditModfile(void *object, ModioResponse response, ModioModfile modfile)
{
  bool *wait = object;
  printf("Edit modfile response: %i\n", response.code);
  if (response.code == 200)
  {
    printf("Modfile edited successfully!\n");
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, (char *)"e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // In order to edit a modfile you will need the mod and modfile id
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Please enter the modfile id: \n");
  u32 modfile_id;
  scanf("%i", &modfile_id);

  printf("Editing modfile...\n");

  // The Modfile Editor helps setting up the fields that will be edited
  // Notice that the version field and modfile zip can't be edited, if you want to change them you should upload a new modfile instead
  ModioModfileEditor modfile_editor;
  modioInitModfileEditor(&modfile_editor);
  modioSetModfileEditorActive(&modfile_editor, false);
  modioSetModfileEditorChangelog(&modfile_editor, (char *)"Stuff was changed on this mod via the examples.");
  modioSetModfileEditorMetadataBlob(&modfile_editor, (char *)"The metadata was edited via the SDK examples.");

  // Once the modfile editor is set we are ready to edit the modfile
  modioEditModfile(&wait, mod_id, modfile_id, modfile_editor, &onEditModfile);

  modioFreeModfileEditor(&modfile_editor);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
