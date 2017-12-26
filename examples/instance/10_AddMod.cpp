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

  //The logo, name, homepage, summary, and tags are mandatory
  mod_handler.setLogoPath("ModExample/logo.png");
  mod_handler.setName("Example Mod Test30");
  mod_handler.setHomepage("http://www.webpage.com");
  mod_handler.setSummary("Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples.");
  mod_handler.addTag("Easy");
  mod_handler.addTag("Medium");

  // The price, stock, description, metadata blob, nameid and modfile are optional
  mod_handler.setPrice(1.99);
  mod_handler.setStock(25);
  mod_handler.setDescription("This mod description was added via the SDK examples. This mod description was added via the SDK examples.");
  mod_handler.setMetadata("Optional metadata");
  //mod_handler.setNameid("my-example-mod"); //Name id must be unique
  //mod_handler.setModfile(int modfile); //Modfile should exist

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

  modioShutdown();

  std::cout << "Process finished" << std::endl;

  return 0;
}
