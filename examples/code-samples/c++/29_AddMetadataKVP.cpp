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

  // We add metadata key value pairs to a mod by providing the key and the value contained on a std::pair
  std::map<std::string, std::string> metadata_kvp;
  metadata_kvp["pistol-dmg"] = "800";

  modio_instance.addMetadataKVP(mod_id, metadata_kvp, [&](const modio::Response &response) {
    std::cout << "Add metadta kvp response: " << response.code << std::endl;
    if (response.code == 201)
    {
      std::cout << "Metadata KVP added successfully" << std::endl;
    }
    finish();
  });

  wait();

  std::cout << "Process finished" << std::endl;

  return 0;
}
