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

  // We delete a mod providing the Mod id
  modio_instance.deleteMod(mod_id, [&](const modio::Response& response, u32 mod_id)
  {
    std::cout << "Mod Delete response: " << response.code << std::endl;
    if(response.code == 204)
    {
      std::cout << "Mod delete successfully" << std::endl;
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
