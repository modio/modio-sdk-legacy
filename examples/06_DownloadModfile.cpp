#include "ModIOInstance.h"

int main(void)
{
  modio::Instance modio_instance(7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto wait = [&]()
  {
    while (!finished)
    {
      modio::sleep(10);
      modioProcess();
    }
  };

  auto finish = [&]()
  {
    finished = true;
  };

  // Let's start by requesting a single mod
  modio::Filter filter;
  filter.setFilterLimit(1);

  std::cout <<"Getting mods..." << std::endl;

  modio_instance.getMods(filter, [&](const modio::Response& response, const std::vector<modio::Mod> & mods)
  {
    std::cout << "On mod get response: " << response.code << std::endl;
    if(response.code == 200 && mods.size() >= 1)
    {
      modio::Mod mod = mods[0];
      std::cout << "Requested mod: " << mod.name << std::endl;

      std::cout << "Installing modfile..." << std::endl;

      // Now we provide the Modfile id and the local path where the modfile will be installed
      modio_instance.installModfile(mod.modfile, "mods_dir/modfile", [&](const modio::Response& response, const std::string& path)
      {
        std::cout << "Install Modfile response: " << response.code << std::endl;

        if(response.code == 200)
        {
          std::cout << "Modfile installed successfully!" << std::endl;
        }

        finish();
      });
    }
  });

  wait();

  modioShutdown();

  std::cout << "Process finished" << std::endl;

  return 0;
}
