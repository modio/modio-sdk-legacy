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

  u32 mod_id;
  std::cout << "Enter the mod id: " << std::endl;
  std::cin >> mod_id;

  std::cout << "Getting mod..." << std::endl;

  modio_instance.getMod(mod_id, [&](const modio::Response &response, const modio::Mod &mod) {
    std::cout << "On mod get response: " << response.code << std::endl;
    if (response.code == 200)
    {
      std::cout << "Name: " << mod.name << std::endl;
      std::cout << "Homepage url: " << mod.homepage_url << std::endl;
      std::cout << "Summary: " << mod.summary << std::endl;
      std::cout << "Tags: " << std::endl;
      for (auto &tag : mod.tags)
        std::cout << "* " << tag.name << std::endl;
      std::cout << "Description: " << mod.description << std::endl;
      std::cout << "Description (plain text): " << mod.description_plaintext << std::endl;
      std::cout << "Metadata blob: " << mod.metadata_blob << std::endl;
      std::cout << "Visible: " << mod.visible << std::endl;
      std::cout << "Maturity option: " << mod.maturity_option << std::endl;
      std::cout << "Logo url: " << mod.logo.original << std::endl;
      std::cout << "Date added: " << mod.date_added << std::endl;
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
