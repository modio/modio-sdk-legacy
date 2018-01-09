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

  // Now we provide the mod id and the local image path to upload the new logo. Thumbnails will be generated automatically
  modio_instance.editModLogo(mod_id, "../ModExample/logo.png", [&](const modio::Response& response, u32 mod_id)
  {
    std::cout << "Edit Mod Logo response: " << response.code << std::endl;

    if(response.code == 200)
    {
      std::cout << "Image uploaded successfully!" << std::endl;
    }

    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
