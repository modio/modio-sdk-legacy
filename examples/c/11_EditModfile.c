#include "modio_c.h"

void onModfileEdited(void* object, ModioResponse response, ModioModfile modfile)
{
  bool* wait = object;
  printf("Edit Mod response: %i\n", response.code);
  if(response.code == 200)
  {
    printf("Mod edited successfully!\n");
  }
  *wait = false;
}

void onModGet(void* object, ModioResponse response, ModioMod mod)
{
  bool* wait = object;
  printf("On mod get response: %i\n",response.code);
  if(response.code == 200)
  {
    printf("Id:\t%i\n",mod.id);
    printf("Name:\t%s\n",mod.name);

    printf("Editing modfile...\n");

    // The Modfile Editor helps setting up the fields that will be edited
    // Notice that the version field and modfile zip can't be edited, you should be uploading another modfile instead
    ModioModfileEditor modfile_editor;
    modioInitModfileEditor(&modfile_editor);
    modioSetModfileEditorActive(&modfile_editor,false);
    modioSetModfileEditorChangelog(&modfile_editor,(char*)"Stuff was changed on this mod via the examples.");

    modioEditModfile(wait, mod.id, mod.modfile.id, modfile_editor, &onModfileEdited);

    modioFreeModfileEditor(&modfile_editor);
  }else
  {
    *wait = false;
  }
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  bool wait = true;

  // Let's start by requesting a single mod
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Getting mod...\n");
  modioGetMod(&wait, mod_id, &onModGet);

  while(wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
