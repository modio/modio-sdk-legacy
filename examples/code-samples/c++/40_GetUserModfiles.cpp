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

  // Before requesting mods, let's define the query filters
  modio::FilterCreator filter;
  filter.setLimit(7);
  filter.setCacheMaxAgeSeconds(100);

  std::cout << "Getting modfiles..." << std::endl;

  // Now we finished setting up the filters we are ready to request the mods
  modio_instance.getUserModfiles(filter, [&](const modio::Response &response, const std::vector<modio::Modfile> &modfiles) {
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
        std::cout << "Metadata:\t" << modfile.metadata_blob << std::endl;
      }
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
