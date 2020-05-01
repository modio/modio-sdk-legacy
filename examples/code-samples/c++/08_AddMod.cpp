#include "modio.h"
#include <iostream>

int main(void)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto wait = [&]() {
    while (!finished)
    {
      modio_instance.sleep(10);
      modio_instance.process();
    }
  };

  auto finish = [&]() {
    finished = true;
  };

  // The Mod Creator helps setting up the fields before creating a Mod
  modio::ModCreator mod_creator;
  mod_creator.setLogoPath("../ModExample/logo.png");
  mod_creator.setName("Example Mod Test30");
  mod_creator.setHomepageURL("http://www.webpage.com");
  mod_creator.setSummary("Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples. Mod added via the SDK examples.");
  mod_creator.addTag("Easy");
  mod_creator.addTag("Medium");
  mod_creator.setDescription("This mod description was added via the SDK examples. This mod description was added via the SDK examples.");
  mod_creator.setMetadataBlob("Optional metadata");
  mod_creator.setVisible(MODIO_PUBLIC);
  mod_creator.setMaturityOption(MODIO_MATURITY_ALCOHOL | MODIO_MATURITY_VIOLENCE);

  std::cout << "Creating mod..." << std::endl;

  // Now we can create the new mod. Remember, this mod wont have a Modfile right away, you should be adding one after the mod was created successfully
  modio_instance.addMod(mod_creator, [&](const modio::Response &response, const modio::Mod &mod) {
    std::cout << "On mod get response: " << response.code << std::endl;
    if (response.code == 201)
    {
      std::cout << "Mod created successfully" << std::endl;
      std::cout << "Mod id:" << mod.id << std::endl;
      std::cout << "Mod name:" << mod.name << std::endl;
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
