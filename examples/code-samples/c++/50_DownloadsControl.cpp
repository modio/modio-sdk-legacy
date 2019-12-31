#include "modio.h"
#include <iostream>

int main(void)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;
  volatile static bool prompt_menu = true;

  auto finish = [&]() {
    finished = true;
  };

  // In this example we are going to queue two mods downloads.
  u32 mod_id;
  std::cout << "Enter a mod id to download: " << std::endl;
  std::cin >> mod_id;
  modio_instance.downloadMod(mod_id);

  std::cout << "Enter another mod id to download: " << std::endl;
  std::cin >> mod_id;
  modio_instance.downloadMod(mod_id);

  std::cout << "Downloading mods..." << std::endl;

  modio_instance.setDownloadListener([&](u32 response_code, u32 mod_id) {
    std::cout << "Download mod response: " << response_code << std::endl;
    if (response_code == 200)
    {
      std::cout << "Mod " << mod_id << " download successfully" << std::endl;
      std::cout << "Installing downloaded mods" << std::endl;
      modio_instance.installDownloadedMods();
    }
    if (modio_instance.getModDownloadQueue().size() == 0)
      finish();
  });

  while (!finished)
  {
    modio_instance.sleep(10);

#ifdef MODIO_WINDOWS_DETECTED
    system("cls");
#endif

    modio_instance.process();

    // The download queue contains all the information about the current downloads
    std::list<modio::QueuedModDownload *> mod_download_queue = modio_instance.getModDownloadQueue();

    std::cout << std::endl;
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

      // Depending on the current download state, there are multiple options that can be given to the user to control their downloads
      switch (current_download->state)
      {
      case MODIO_MOD_STARTING_DOWNLOAD:
      {
        std::cout << "Starting download. Please wait..." << std::endl;
        break;
      }
      case MODIO_MOD_DOWNLOADING:
      {
        if (current_download->current_progress == 0)
        {
          std::cout << "Download started. Please wait..." << std::endl;
        }
        else
        {
          std::cout << "Menu:" << std::endl;
          std::cout << "=====" << std::endl;
          std::cout << "1. Continue" << std::endl;
          std::cout << "2. Pause" << std::endl;
          std::cout << "3. Stop asking" << std::endl;
          std::cout << "4. Prioritize download" << std::endl;
          std::cout << "5. Exit" << std::endl;
          std::cout << "Option: " << std::endl;
          std::cin >> option;

          if (option == "2")
            modio_instance.pauseDownloads();
          if (option == "3")
            prompt_menu = false;
          if (option == "4")
          {
            u32 mod_id;
            std::cout << "Enter the mod id to prioritize: " << std::endl;
            std::cin >> mod_id;
            modio_instance.prioritizeModDownload(mod_id);
          }
          if (option == "5")
            finish();
        }
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
