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

        modio::ModHandler mod_handler;
        //Required fields
        mod_handler.setLogoPath("ModExample/logo.png");
        mod_handler.setName("Update Example");
        mod_handler.setHomepage("http://www.updated.com");
        mod_handler.setSummary("Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples.");
        mod_handler.addTag("Easy");
        //Optional fields
        mod_handler.setPrice(2.99);
        //mod_handler.setStock(50);//The developer should allow mods to control mod supply and scarcity
        mod_handler.setDescription("This mod description was updated via the SDK examples. This mod description was updated via the SDK examples.");
        mod_handler.setMetadata("Optional updated metadata");
        //mod_handler.setNameid("my-example-mod"); //Name id must be unique
        //mod_handler.setModfile(int modfile); //Modfile should exist

        std::cout <<"Editing mod..." << std::endl;

        mod.editMod(NULL, mods[i].id, mod_handler, [&](void* object, const modio::Response& response, const modio::Mod& mod)
        {
          std::cout << "On mod get response: " << response.code << std::endl;
          if(response.code == 200)
          {
            std::cout << "Mod created successfully" << std::endl;
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
