#include "modio.h"

int main(void)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

  volatile static bool finished = false;

  auto wait = [&]() {
    while (!finished)
    {
      modio_instance.sleep(10);
      modio_instance.process();

      std::list<modio::QueuedModfileUpload *> modfile_upload_queue = modio_instance.getModfileUploadQueue();

      if (modfile_upload_queue.size() > 0)
      {
        // We can track the upload progress by looking into the mod upload queue
        modio::QueuedModfileUpload *current_upload = *(modfile_upload_queue.begin());
        double current_progress = current_upload->current_progress;
        double total_size = current_upload->total_size;
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

  // The Modfile Creator helps us setting up the modfile fields and the mod directory that will be zipped and uploaded
  modio::ModfileCreator modfile_creator;
  modfile_creator.setPath("../ModExample/modfile/");
  modfile_creator.setVersion("v1.1.0");
  modfile_creator.setChangelog("This is a change log, this is a changelog , this is a changelog , this is a changelog , this is a changelog , this is a changelog, this is a changelog , this is a changelog , this is a changelog");
  modfile_creator.setMetadataBlob("This metadata was added via the SDK examples.");
  modfile_creator.setActive(true);

  std::cout << "Uploading modfile..." << std::endl;

  modio_instance.addModfile(mod_id, modfile_creator);

  modio_instance.setUploadListener([&](u32 response_code, u32 mod_id) {
    std::cout << "Add Modfile response: " << response_code << std::endl;

    if (response_code == 201)
    {
      std::cout << "Modfile added successfully!" << std::endl;
    }

    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
