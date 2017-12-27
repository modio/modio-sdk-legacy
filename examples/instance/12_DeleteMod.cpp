#include "instance/ModIOInstance.h"

int main(void)
{
  modio::Instance modio_instance(7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto wait = [&]()
  {
    while (!finished)
    {
      modio_instance.sleep(10);
      modioProcess();
    }
  };

  auto finish = [&]()
  {
    finished = true;
  };

  // Let's start by requesting a single mod
  modio::FilterHandler filter;
  filter.setLimit(1);

  std::cout <<"Getting mods..." << std::endl;

  modio_instance.getMods(filter, [&](const modio::Response& response, const std::vector<modio::Mod> & mods)
  {
    std::cout << "On mod get response: " << response.code << std::endl;
    if(response.code == 200 && mods.size() >= 1)
    {
      modio::Mod mod = mods[0];
      std::cout << "Requested mod: " << mod.name << std::endl;

      std::cout << "Deleting mod..." << std::endl;

      // We delete a mod providing the Mod id
      modio_instance.deleteMod(mod.id, [&](const modio::Response& response, u32 mod_id)
      {
        std::cout << "Mod Delete response: " << response.code << std::endl;
        if(response.code == 204)
        {
          std::cout << "Mod delete successfully" << std::endl;
        }
        finish();
      });
    }
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
