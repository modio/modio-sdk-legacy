#include "instance/ModIOInstance.h"

int main(void)
{
  modio::Instance modio_instance(7, "e91c01b8882f4affeddd56c96111977b");

  if( modio_instance.getInstalledModfilesCount() > 0 )
  {
    if( modio_instance.uninstallModfile(modio_instance.getInstalledModfileIds()[0]) )
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

  modioShutdown();

  std::cout << "Process finished" << std::endl;

  return 0;
}
