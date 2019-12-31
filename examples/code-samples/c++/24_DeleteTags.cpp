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

  std::vector<std::string> tags;
  tags.push_back("Hard");

  // We delete tags by providing the selected Mod id and the tag names
  modio_instance.deleteModTags(mod_id, tags, [&](const modio::Response &response) {
    std::cout << "Add tags response: " << response.code << std::endl;
    if (response.code == 204)
    {
      std::cout << "Tags deleted successfully" << std::endl;
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
