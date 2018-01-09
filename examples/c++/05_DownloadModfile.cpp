#include "modio.h"

int main(void)
{
  modio::Instance modio_instance(7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;
  volatile static u32 download_modfile_id = -1;

  auto wait = [&]()
  {
    while (!finished)
    {
      modio_instance.sleep(10);
      modioProcess();
      if(download_modfile_id != -1)
      {
        // Track download progress by providing the modfile id
        double progress = modio_instance.getModfileDownloadPercentage(download_modfile_id);
        if(progress > 0)
          std::cout << "Download progress: " << progress << "%" << std::endl;
      }
    }
  };

  auto finish = [&]()
  {
    finished = true;
  };

  u32 mod_id;
  std::cout << "Enter the mod id: " << std::endl;
  std::cin >> mod_id;

  std::cout <<"Getting mods..." << std::endl;

  modio_instance.getMod(mod_id, [&](const modio::Response& response, const modio::Mod& mod)
  {
    std::cout << "On mod get response: " << response.code << std::endl;
    if(response.code == 200)
    {
      std::cout << "Requested mod: " << mod.name << std::endl;

      std::cout << "Installing modfile..." << std::endl;

      download_modfile_id = mod.modfile.id;

      // Now we provide the Modfile id and the local path where the modfile will be installed
      modio_instance.installModfile(mod.modfile, "../mods_dir/modfile", [&](const modio::Response& response)
      {
        std::cout << "Install Modfile response: " << response.code << std::endl;

        if(response.code == 200)
        {
          std::cout << "Modfile installed successfully!" << std::endl;
        }

        finish();
      });
    }else
    {
      finish();
    }
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
