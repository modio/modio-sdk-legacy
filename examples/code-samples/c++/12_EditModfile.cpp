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

  // In order to edit a modfile you will need the mod and modfile id
  u32 mod_id;
  std::cout << "Enter the mod id: " << std::endl;
  std::cin >> mod_id;

  u32 modfile_id;
  std::cout << "Enter the modfile id: " << std::endl;
  std::cin >> modfile_id;

  // The Modfile Editor helps setting up the fields that will be edited
  // Notice that the version field and modfile zip can't be edited, if you want to change them you should upload a new modfile instead
  modio::ModfileEditor modfile_editor;
  modfile_editor.setActive(true);
  modfile_editor.setChangelog("Stuff was changed on this mod via the examples.");
  modfile_editor.setMetadataBlob("This metadata was edited via the SDK examples.");

  std::cout << "Editing modfile..." << std::endl;

  // Once the modfile editor is set we are ready to edit the modfile
  modio_instance.editModfile(mod_id, modfile_id, modfile_editor, [&](const modio::Response &response, const modio::Modfile &modfile) {
    std::cout << "Edit Modfile response: " << response.code << std::endl;

    if (response.code == 200)
    {
      std::cout << "Modfile edited successfully!" << std::endl;
    }

    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
