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

  // Just like mods and other schemas, modfiles can be filtered using the Filter Creator
  modio::FilterCreator filter;
  filter.setLimit(7);
  filter.setCacheMaxAgeSeconds(100);

  u32 mod_id;
  std::cout << "Enter the mod id: " << std::endl;
  std::cin >> mod_id;

  std::cout << "Getting modfiles..." << std::endl;

  // Now we finished setting up the filters we are ready to request the modfiles
  modio_instance.getAllModfiles(mod_id, filter, [&](const modio::Response &response, const std::vector<modio::Modfile> &modfiles) {
    std::cout << "On get modfiles response: " << response.code << std::endl;
    if (response.code == 200)
    {
      std::cout << "Listing modfiles" << std::endl;
      std::cout << "================" << std::endl;
      for (auto &modfile : modfiles)
      {
        std::cout << "Id: \t" << modfile.id << std::endl;
        std::cout << "Version:\t" << modfile.version << std::endl;
        std::cout << "Changelog:\t" << modfile.changelog << std::endl;
        std::cout << "Metadata blob:\t" << modfile.metadata_blob << std::endl;
      }
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
