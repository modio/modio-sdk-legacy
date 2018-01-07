#include "c++/ModIOInstance.h"

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

  // Let's start by requesting a single mod
  modio::FilterCreator filter;
  filter.setLimit(1);

  std::cout <<"Getting mods..." << std::endl;

  modio_instance.getMods(filter, [&](const modio::Response& response, const std::vector<modio::Mod> & mods)
  {
    std::cout << "On mod get response: " << response.code << std::endl;
    if(response.code == 200 && mods.size() >= 1)
    {
      modio::Mod mod = mods[0];
      std::cout << "Requested mod: " << mod.name << std::endl;

      // The Mod Editor helps setting up the fields that will be updated
      modio::ModEditor mod_editor;
      mod_editor.setName("Update Example");
      mod_editor.setHomepage("http://www.updated.com");
      mod_editor.setSummary("Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples. Mod updated via the SDK examples.");
      mod_editor.setDescription("This mod description was updated via the SDK examples. This mod description was updated via the SDK examples.");
      mod_editor.setMetadataBlob("Optional updated metadata");

      std::cout <<"Editing mod..." << std::endl;

      modio_instance.editMod(mod.id, mod_editor, [&](const modio::Response& response, const modio::Mod& mod)
      {
        std::cout << "On mod get response: " << response.code << std::endl;
        if(response.code == 200)
        {
          std::cout << "Mod created successfully" << std::endl;
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
