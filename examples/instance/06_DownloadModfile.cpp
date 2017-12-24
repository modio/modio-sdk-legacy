#include "instance/ModIOInstance.h"

int main(void)
{
  modio::Instance modio_instance(7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;
  volatile static int download_mod_id = -1;

  auto wait = [&]()
  {
    while (!finished)
    {
      modio_instance.sleep(10);
      modioProcess();
      if(download_mod_id != -1)
      {
        double progress = modio_instance.getModfileDownloadPercentage(download_mod_id);
        if(progress > 0)
          std::cout << "Download progress: " << progress << "%" << std::endl;
      }
    }
  };

  auto finish = [&]()
  {
    finished = true;
  };

  // Let's start by requesting a single mod
  modio::FilterHandler filter;
  filter.setLimit(1);

  std::cout <<"Getting mods..." << std::endl;

  modio_instance.getMods(filter, [&](const modio::Response& response, const std::vector<modio::Mod> & mods)
  {
    std::cout << "On mod get response: " << response.code << std::endl;
    if(response.code == 200 && mods.size() >= 1)
    {
      modio::Mod mod = mods[0];
      std::cout << "Requested mod: " << mod.name << std::endl;

      std::cout << "Installing modfile..." << std::endl;

      download_mod_id = mod.modfile.id;

      // Now we provide the Modfile id and the local path where the modfile will be installed
      modio_instance.installModfile(mod.modfile, "mods_dir/modfile", [&](const modio::Response& response)
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
