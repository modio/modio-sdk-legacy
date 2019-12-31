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

  // In order to delete a modfile you will need the mod and modfile id
  u32 mod_id;
  std::cout << "Enter the mod id: " << std::endl;
  std::cin >> mod_id;

  u32 modfile_id;
  std::cout << "Enter the modfile id: " << std::endl;
  std::cin >> modfile_id;

  std::cout << "Deleting modfile..." << std::endl;

  modio_instance.deleteModfile(mod_id, modfile_id, [&](const modio::Response &response) {
    std::cout << "Delete Modfile response: " << response.code << std::endl;

    if (response.code == 204)
    {
      std::cout << "Modfile deleted successfully!" << std::endl;
    }

    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
