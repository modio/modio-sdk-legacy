#include "modio.h"
#include <iostream>

int main(void)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  std::vector<modio::InstalledMod> installed_mods = modio_instance.getAllInstalledMods();

  // First, let's check if there is at least one modfile installed
  if (installed_mods.size() > 0)
  {
    // Now we delete the local modfile folder by providing the modfile id
    modio_instance.uninstallMod(installed_mods[0].mod.id);
    std::cout << "Modfile uninstalled successfully." << std::endl;
  }
  else
  {
    std::cout << "There are no Modfiles installed, please try installing one before running this example again." << std::endl;
  }

  std::cout << "Process finished" << std::endl;

  return 0;
}
