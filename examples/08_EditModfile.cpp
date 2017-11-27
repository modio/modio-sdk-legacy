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

      // The Modfile Handler helps setting up the fields that will be edited
      // Notice that the version field and modfile zip can't be edited, you should be uploading another modfile instead
      modio::ModfileHandler modfile_handler;
      modfile_handler.setModfileActive(true);
      modfile_handler.setModfileChangelog("Stuff was changed on this mod via the examples.");

      std::cout << "Uploading modfile..." << std::endl;

      mod.editModfile(NULL, requested_mod.id, requested_mod.modfile.id, modfile_handler, [&](void* object, const modio::Response& response, const modio::Modfile& modfile)
      {
        std::cout << "Add Modfile response: " << response.code << std::endl;

        if(response.code == 200)
        {
          std::cout << "Modfile added successfully!" << std::endl;
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
