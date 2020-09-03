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

  bool vote;
  std::cout << "Enter 1 for a positive rating or 0 for a negative one: " << std::endl;
  std::cin >> vote;

  std::cout << "Adding mod rating..." << std::endl;

  modio_instance.addModRating(mod_id, vote, [&](const modio::Response &response) {
    std::cout << "Add mod rating response: " << response.code << std::endl;
    if (response.code == 201)
    {
      std::cout << "Ratting added!" << std::endl;
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
