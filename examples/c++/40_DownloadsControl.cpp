#include "modio.h"

int main(void)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;
  volatile static bool prompt_menu = true;
  volatile static u32 download_mod_id = -1;

  auto finish = [&]() {
    finished = true;
  };

  u32 mod_id;
  std::cout << "Enter the mod id: " << std::endl;
  std::cin >> mod_id;
  download_mod_id = mod_id;

  std::cout << "Installing mod..." << std::endl;

  modio_instance.installMod(mod_id);

  while (!finished)
  {
    modio_instance.sleep(10);
    modio_instance.process();

    std::list<modio::QueuedModDownload *> mod_download_queue = modio_instance.getModDownloadQueue();
    system("cls");
    std::cout << "Download queue:" << std::endl;
    std::cout << "===============" << std::endl;
    for (auto &queued_mod_download : mod_download_queue)
    {
      std::cout << "Name: " << queued_mod_download->mod.name << std::endl;
      std::cout << "id: " << queued_mod_download->mod.id << std::endl;
      double current_progress = queued_mod_download->current_progress;
      double total_size = queued_mod_download->total_size;
      std::cout << "Progress: " << (current_progress / total_size) * 100.0 << "%" << std::endl;
      std::cout << std::endl;
    }
    std::cout << std::endl;

    if (prompt_menu && mod_download_queue.size() > 0)
    {
      std::string option;

      modio::QueuedModDownload *current_download = *(modio_instance.getModDownloadQueue().begin());

      switch (current_download->state)
      {
      case MODIO_MOD_STARTING_DOWNLOAD:
      {
        std::cout << "Starting download. Please wait..." << std::endl;
        break;
      }
      case MODIO_MOD_DOWNLOADING:
      {
        std::cout << "Menu:" << std::endl;
        std::cout << "=====" << std::endl;
        std::cout << "1. Continue" << std::endl;
        std::cout << "2. Pause" << std::endl;
        std::cout << "3. Stop asking" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Option: " << std::endl;
        std::cin >> option;

        if (option == "2")
          modio_instance.pauseDownloads();
        if (option == "3")
          prompt_menu = false;
        if (option == "4")
          finish();
        break;
      }
      case MODIO_MOD_PAUSING:
      {
        std::cout << "Pausing. Please wait..." << std::endl;
        break;
      }
      case MODIO_MOD_PAUSED:
      {
        std::cout << "Menu:" << std::endl;
        std::cout << "=====" << std::endl;
        std::cout << "1. Continue" << std::endl;
        std::cout << "2. Resume" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Option: " << std::endl;
        std::cin >> option;

        if (option == "2")
          modio_instance.resumeDownloads();
        if (option == "3")
          finish();
        break;
      }
      }
    }
  }

  std::cout << "Process finished" << std::endl;

  return 0;
}
