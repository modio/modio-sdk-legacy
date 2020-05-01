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

  // We add tags to a mod by providing the tag names. Remember, they must be valid tags allowed by the parrent game
  modio_instance.addModTags(mod_id, tags, [&](const modio::Response &response) {
    std::cout << "Add tags response: " << response.code << std::endl;
    if (response.code == 201)
    {
      std::cout << "Tags added successfully" << std::endl;
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
