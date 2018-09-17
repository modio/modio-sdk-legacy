#include "c++/ModIOInstance.h"

namespace modio
{
  Instance::Instance(u32 environment, u32 game_id, const std::string& api_key)
  {
    this->current_call_id = 0;
    modioInit(environment, game_id, (char*)api_key.c_str(), NULL);
  }

  Instance::Instance(u32 environment, u32 game_id, const std::string& api_key, const std::string& root_path)
  {
    this->current_call_id = 0;
    modioInit(environment, game_id, (char*)api_key.c_str(), (char*)root_path.c_str());
  }

  void Instance::setDebugLevel(u32 debug_level)
  {
    modioSetDebugLevel(debug_level);
  }

  void Instance::sleep(u32 milliseconds)
  {
    modioSleep(milliseconds);
  }

  void Instance::compressFiles(std::string root_directory, std::vector<std::string> filenames, std::string zip_path)
  {
    modio::minizipwrapper::compressFiles(root_directory, filenames, zip_path);
  }

  void Instance::process()
  {
    modioProcess();
  }
}
