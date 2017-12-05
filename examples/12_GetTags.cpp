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
  modio::FilterHandler filter;
  filter.setFilterLimit(1);

  std::cout <<"Getting mods..." << std::endl;

  modio_instance.getMods(filter, [&](const modio::Response& response, const std::vector<modio::Mod> & mods)
  {
    std::cout << "On mod get response: " << response.code << std::endl;
    if(response.code == 200 && mods.size() >= 1)
    {
      modio::Mod mod = mods[0];
      std::cout << "Requested mod: " << mod.name << std::endl;

      std::cout <<"Getting tags..." << std::endl;

      // We request the list of tags by providing the Mod's id
      modio_instance.getTags(mod.id, [&](const modio::Response& response, std::vector<modio::Tag> tags)
      {
        std::cout << "Get tags response: " << response.code << std::endl;
        if(response.code == 200)
        {
          std::cout << "Mod delete successfully" << std::endl;
          std::cout << "Listing Tags" << std::endl;
          std::cout << "============" << std::endl;
          for(auto& tag : tags)
          {
            std::cout << tag.name << std::endl;
          }
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
