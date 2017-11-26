#include "ModIOInstance.h"

int main(void)
{
  modio::Instance mod(7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto wait = [&]()
  {
    while (!finished)
    {
      modio::sleep(100);
      modioProcess();
    }
  };

  auto finish = [&]()
  {
    finished = true;
  };

  modio::Filter filter;
  filter.setFilterLimit(1);

  std::cout <<"Getting mods..." << std::endl;

  mod.getMods(NULL, filter, [&](void* object, const modio::Response& response, const std::vector<modio::Mod> & mods)
  {
    std::cout << "On mod get response: " << response.code << std::endl;
    if(response.code == 200)
    {
      std::cout << "Listing mods" << std::endl;
      std::cout << "============" << std::endl;
      for(int i=0; i < (int)mods.size(); i++)
      {
        std::cout << "Mod[" << i << "]" << std::endl;
        std::cout << "Id: \t" << mods[i].id << std::endl;
        std::cout << "Name:\t" << mods[i].name << std::endl;

        std::cout <<"Getting tags..." << std::endl;

        mod.getTags(NULL, mods[i].id, [&](void* object, const modio::Response& response, std::vector<modio::Tag> tags)
        {
          std::cout << "Get tags response: " << response.code << std::endl;
          if(response.code == 200)
          {
            std::cout << "Mod delete successfully" << std::endl;
            std::cout << "Listing Tags" << std::endl;
            std::cout << "============" << std::endl;
            for(int i=0; i < (int)tags.size(); i++)
            {
              std::cout << tags[i].tag << std::endl;
            }
          }
          finish();
        });
      }
    }
  });

  wait();

  modioShutdown();

  std::cout << "Process finished" << std::endl;

  return 0;
}
