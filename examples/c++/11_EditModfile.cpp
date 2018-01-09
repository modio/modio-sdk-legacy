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

  std::cout <<"Getting mods..." << std::endl;

  modio_instance.getMod(mod_id, [&](const modio::Response& response, const modio::Mod& mod)
  {
    std::cout << "On mod get response: " << response.code << std::endl;
    if(response.code == 200)
    {
      std::cout << "Requested mod: " << mod.name << std::endl;

      // The Modfile Editor helps setting up the fields that will be edited
      // Notice that the version field and modfile zip can't be edited, you should be uploading another modfile instead
      modio::ModfileEditor modfile_editor;
      modfile_editor.setActive(true);
      modfile_editor.setChangelog("Stuff was changed on this mod via the examples.");

      std::cout << "Uploading modfile..." << std::endl;

      modio_instance.editModfile(mod.id, mod.modfile.id, modfile_editor, [&](const modio::Response& response, const modio::Modfile& modfile)
      {
        std::cout << "Add Modfile response: " << response.code << std::endl;

        if(response.code == 200)
        {
          std::cout << "Modfile added successfully!" << std::endl;
        }

        finish();
      });
    }else
    {
      finish();
    }
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
