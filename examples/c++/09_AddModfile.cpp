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

  // The Modfile Creator helps us setting up the modfile fields and the mod directory that will be zipped and uploaded
  modio::ModfileCreator modfile_creator;
  modfile_creator.setPath("../ModExample/modfile/");
  modfile_creator.setVersion("v1.1.0");
  modfile_creator.setChangelog("This is a change log, this is a changelog , this is a changelog , this is a changelog , this is a changelog , this is a changelog, this is a changelog , this is a changelog , this is a changelog");
  modfile_creator.setActive(true);

  std::cout << "Uploading modfile..." << std::endl;

  modio_instance.addModfile(mod_id, modfile_creator, [&](const modio::Response& response, const modio::Modfile& modfile)
  {
    std::cout << "Add Modfile response: " << response.code << std::endl;

    if(response.code == 201)
    {
      std::cout << "Modfile added successfully!" << std::endl;
    }

    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
