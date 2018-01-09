#include "modio.h"

int main(void)
{
  modio::Instance modio_instance(7, "e91c01b8882f4affeddd56c96111977b");

  std::vector<u32> modfile_ids = modio_instance.getInstalledModfileIds();

  // First, let's check if there is at least one modfile installed
  if( modfile_ids.size() > 0 )
  {
    // Now we delete the local modfile folder by providing the modfile id
    if( modio_instance.uninstallModfile(modfile_ids[0]) )
    {
      std::cout << "Modfile uninstalled successfully." << std::endl;
    }else
    {
      std::cout << "Error uninstalling modfile." << std::endl;
    }
  }else
  {
    std::cout << "There are no Modfiles installed, please try installing one before running this example again." << std::endl;
  }

  std::cout << "Process finished" << std::endl;

  return 0;
}
