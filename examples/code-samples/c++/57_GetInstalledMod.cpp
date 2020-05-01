#include "modio.h"
#include <iostream>

int main(void)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  u32 mod_id;
  std::cout << "Enter the mod id: " << std::endl;
  std::cin >> mod_id;
  
  modio::InstalledMod installed_mod = modio_instance.getInstalledMod(mod_id);

  // First, let's check if there is at least one modfile installed
  if (installed_mod.mod_id != 0)
  {
    // Now we delete the local modfile folder by providing the modfile id
    std::cout << "Mod name: " << installed_mod.mod.name << std::endl;
    std::cout << "Mod path: " << installed_mod.path << std::endl;
  }
  else
  {
    std::cout << "That mod is not installed." << std::endl;
  }

  std::cout << "Process finished" << std::endl;

  return 0;
}