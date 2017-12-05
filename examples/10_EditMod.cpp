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

      // The Mod Handler helps setting up the fields that will be updated
      modio::ModHandler mod_handler;
      mod_handler.setLogoPath("ModExample/logo.png");
      mod_handler.setName("Update Example");
      mod_handler.setHomepage("http://www.updated.com");
      mod_handler.setSummary("Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples.");
      mod_handler.addTag("Easy");
      mod_handler.setPrice(2.99);
      //mod_handler.setStock(50);// In order to use Stock features, the game developer should set this up on the mod.io website
      mod_handler.setDescription("This mod description was updated via the SDK examples. This mod description was updated via the SDK examples.");
      mod_handler.setMetadata("Optional updated metadata");
      //mod_handler.setNameid("my-example-mod"); // The Name id must be unique
      //mod_handler.setModfile(int modfile); // The Modfile should exist

      std::cout <<"Editing mod..." << std::endl;

      modio_instance.editMod(mod.id, mod_handler, [&](const modio::Response& response, const modio::Mod& mod)
      {
        std::cout << "On mod get response: " << response.code << std::endl;
        if(response.code == 200)
        {
          std::cout << "Mod created successfully" << std::endl;
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
