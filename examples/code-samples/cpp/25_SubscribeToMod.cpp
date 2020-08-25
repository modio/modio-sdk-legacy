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

  std::cout << "Subscribing to mod..." << std::endl;

  modio_instance.subscribeToMod(mod_id, [&](const modio::Response &response, const modio::Mod &mod) {
    std::cout << "Subscribe mod response: " << response.code << std::endl;
    if (response.code == 201)
    {
      std::cout << "Subscribed to mod!" << std::endl;
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
