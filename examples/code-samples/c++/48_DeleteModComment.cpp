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

  u32 comment_id;
  std::cout << "Enter the comment id: " << std::endl;
  std::cin >> comment_id;

  std::cout << "Getting mods..." << std::endl;

  // Now we finished setting up the filters we are ready to request the mods
  modio_instance.deleteModComment(mod_id, comment_id, [&](const modio::Response &response) {
    std::cout << "On delete mod comment response: " << response.code << std::endl;
    if (response.code == 204)
    {
      std::cout << "Success" << std::endl;
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
