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

  // The Mod Handler helps setting up the fields before creating a Mod
  modio::ModHandler mod_handler;
  mod_handler.setLogoPath("../ModExample/logo.png");
  mod_handler.setName("Example Mod Test30");
  mod_handler.setHomepage("http://www.webpage.com");
  mod_handler.setSummary("Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples.");
  mod_handler.addTag("Easy");
  mod_handler.addTag("Medium");
  mod_handler.setDescription("This mod description was added via the SDK examples. This mod description was added via the SDK examples.");
  mod_handler.setMetadataBlob("Optional metadata");

  std::cout <<"Creating mod..." << std::endl;

  // Now we can create the new mod. Remember, this mod wont have a Modfile right away, you should be adding one after the mod was created successfully
  modio_instance.addMod(mod_handler, [&](const modio::Response& response, const modio::Mod& mod)
  {
    std::cout << "On mod get response: " << response.code << std::endl;
    if(response.code == 201)
    {
      std::cout << "Mod created successfully" << std::endl;
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
