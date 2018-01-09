#include "modio_c.h"

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  u32 installed_modfiles_count = modioGetInstalledModfilesCount();

  // First, let's check if there is at least one modfile installed
  if( installed_modfiles_count > 0 )
  {
    u32 modfile_id = modioGetInstalledModfileId(0);

    // Now we delete the local modfile folder by providing the modfile id
    if( modioUninstallModfile(modfile_id) )
    {
      printf("Modfile uninstalled successfully.\n");

    }else
    {
      printf("Error uninstalling modfile.\n");
    }
  }else
  {
    printf("There are no Modfiles installed, please try installing one before running this example again.\n");
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
