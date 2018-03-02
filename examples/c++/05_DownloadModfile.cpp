#include "modio.h"

int main(void)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;
  volatile static u32 download_mod_id = -1;

  auto wait = [&]()
  {
    while (!finished)
    {
      modio_instance.sleep(10);
      modio_instance.process();
      if(download_mod_id != -1)
      {
        // Track download progress by providing the modfile id
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

  u32 mod_id;
  std::cout << "Enter the mod id: " << std::endl;
  std::cin >> mod_id;
  download_mod_id = mod_id;

  std::cout <<"Installing mod..." << std::endl;

  modio_instance.installMod(mod_id, [&](const modio::Response& response)
  {
    std::cout << "Install Modfile response: " << response.code << std::endl;

    if(response.code == 200)
    {
      std::cout << "Modfile installed successfully!" << std::endl;
    }

    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
