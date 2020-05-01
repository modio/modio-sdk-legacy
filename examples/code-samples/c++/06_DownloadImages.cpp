#include "modio.h"
#include <iostream>

int main(void)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto wait = [&]() {
    while (!finished)
    {
      modio_instance.sleep(10);
      modio_instance.process();
    }
  };

  auto finish = [&]() {
    finished = true;
  };

  u32 mod_id;
  std::cout << "Enter the mod id: " << std::endl;
  std::cin >> mod_id;

  std::cout << "Getting mod..." << std::endl;

  modio_instance.getMod(mod_id, [&](const modio::Response &response, const modio::Mod &mod) {
    std::cout << "On mod get response: " << response.code << std::endl;
    if (response.code == 200)
    {
      std::cout << "Requested mod: " << mod.name << std::endl;

      std::cout << "Downloading image" << std::endl;

      // Now let's download the original logo full size to the selected path
      // Remember, you can also download other images such as headers and media images in different file sizes using the thumbnail fields
      modio_instance.downloadImage(mod.logo.original, "../mods_dir/original.png", [&](const modio::Response &response) {
        std::cout << "Download Image response: " << response.code << std::endl;

        if (response.code == 200)
        {
          std::cout << "Image downloaded successfully!" << std::endl;
        }

        finish();
      });
    }
    else
    {
      finish();
    }
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
