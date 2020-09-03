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

  // To retreive a single modfile we are going to need both the mod and modfile id
  u32 mod_id;
  std::cout << "Enter the mod id: " << std::endl;
  std::cin >> mod_id;

  u32 modfile_id;
  std::cout << "Enter the modfie id: " << std::endl;
  std::cin >> modfile_id;

  std::cout << "Getting modfile..." << std::endl;

  modio_instance.getModfile(mod_id, modfile_id, [&](const modio::Response &response, const modio::Modfile &modfile) {
    std::cout << "On get modfile response: " << response.code << std::endl;
    if (response.code == 200)
    {
      std::cout << "Id: \t" << modfile.id << std::endl;
      std::cout << "Version:\t" << modfile.version << std::endl;
      std::cout << "Changelog:\t" << modfile.changelog << std::endl;
      std::cout << "Metadata blob:\t" << modfile.metadata_blob << std::endl;
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
