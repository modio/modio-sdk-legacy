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

      std::list<modio::QueuedModDownload *> mod_download_queue = modio_instance.getModDownloadQueue();

      if (mod_download_queue.size() > 0)
      {
        // We can track download progress by looking into the mod download queue
        modio::QueuedModDownload *current_download = *(mod_download_queue.begin());
        double current_progress = current_download->current_progress;
        double total_size = current_download->total_size;
        std::cout << "Progress: " << (current_progress / total_size) * 100.0 << "%" << std::endl;
      }
    }
  };

  auto finish = [&]() {
    finished = true;
  };

  u32 mod_id;
  std::cout << "Enter the mod id: " << std::endl;
  std::cin >> mod_id;

  std::cout << "Downloading mod..." << std::endl;

  modio_instance.downloadMod(mod_id);
  modio_instance.setDownloadListener([&](u32 response_code, u32 mod_id) {
    std::cout << "Download mod response: " << response_code << std::endl;

    if (response_code == 200)
    {
      std::cout << "Mod " << mod_id << " downloaded successfully" << std::endl;
      std::cout << "Installing downloaded mods" << std::endl;
      modio_instance.installDownloadedMods();
    }

    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
