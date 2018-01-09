#include "modio.h"

int main(void)
{
  modio::Instance modio_instance(7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto wait = [&]()
  {
    while (!finished)
    {
      modio_instance.sleep(10);
      modioProcess();
    }
  };

  auto finish = [&]()
  {
    finished = true;
  };

  u32 mod_id;
  std::cout << "Enter the mod id: " << std::endl;
  std::cin >> mod_id;

  std::vector<std::string> tags;
  tags.push_back("Hard");

  // We add tags to a mod by providing the tag names. Remember, they must be valid tags allowed by the parrent game
  modio_instance.addTags(mod_id, tags, [&](const modio::Response& response, u32 mod_id)
  {
    std::cout << "Add tags response: " << response.code << std::endl;
    if(response.code == 204)
    {
      std::cout << "Tags added successfully" << std::endl;
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
