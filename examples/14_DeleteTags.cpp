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

      std::cout <<"Adding tags..." << std::endl;

      std::vector<std::string> tags;
      tags.push_back("Easy");

      // We delete tags by providing the selected Mod id and the tag names
      modio_instance.deleteTags(mod.id, tags, [&](const modio::Response& response, u32 mod_id, std::vector<modio::Tag> tags)
      {
        std::cout << "Add tags response: " << response.code << std::endl;
        if(response.code == 204)
        {
          std::cout << "Tags deleted successfully" << std::endl;
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
