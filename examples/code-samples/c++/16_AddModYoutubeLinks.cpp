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

  std::vector<std::string> youtube_links;
  youtube_links.push_back("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
  // Now we provide the mod id and the local image path to upload the new logo. Thumbnails will be generated automatically
  modio_instance.addModYoutubeLinks(mod_id, youtube_links, [&](const modio::Response &response) {
    std::cout << "Edit Mod Logo response: " << response.code << std::endl;

    if (response.code == 200)
    {
      std::cout << "Image uploaded successfully!" << std::endl;
    }

    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
