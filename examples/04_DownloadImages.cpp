#include "ModIOInstance.h"

int main(void)
{
  modio::Instance mod(7, "e91c01b8882f4affeddd56c96111977b");

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

  mod.getMods(NULL, filter, [&](void* object, const modio::Response& response, const std::vector<modio::Mod> & mods)
  {
    std::cout << "On mod get response: " << response.code << std::endl;
    if(response.code == 200 && mods.size() >= 1)
    {
      modio::Mod requested_mod = mods[0];
      std::cout << "Requested mod: " << requested_mod.name << std::endl;

      std::cout << "Downloading image" << std::endl;

      // Now let's download the original logo full size to the selected path
      // Remember, you can also download other images such as headers and media images in different file sizes using the thumbnail fields
      mod.downloadImage(NULL, requested_mod.logo.original, "mods_dir/original.png", [&](void* object, const modio::Response& response, const std::string& path)
      {
        std::cout << "Download Image response: " << response.code << std::endl;

        if(response.code == 200)
        {
          std::cout << "Image downloaded successfully!" << std::endl;
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
