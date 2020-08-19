#include "c++/ModIOInstance.h"
#include <stddef.h>
#include "c++/methods/callbacks/AuthenticationInstanceCallbacks.h"
#include "c++/methods/callbacks/CommentsInstanceCallbacks.h"
#include "c++/methods/callbacks/DependenciesInstanceCallbacks.h"
#include "c++/methods/callbacks/DownloadsInstanceCallbacks.h"
#include "c++/methods/callbacks/ImageInstanceCallbacks.h"
#include "c++/methods/callbacks/MeInstanceCallbacks.h"
#include "c++/methods/callbacks/MediaInstanceCallbacks.h"
#include "c++/methods/callbacks/MetadataKVPInstanceCallbacks.h"
#include "c++/methods/callbacks/ModEventsInstanceCallbacks.h"
#include "c++/methods/callbacks/ModInstanceCallbacks.h"
#include "c++/methods/callbacks/ModStatsInstanceCallbacks.h"
#include "c++/methods/callbacks/ModfileInstanceCallbacks.h"
#include "c++/methods/callbacks/RatingsInstanceCallbacks.h"
#include "c++/methods/callbacks/ReportsInstanceCallbacks.h"
#include "c++/methods/callbacks/SubscriptionsInstanceCallbacks.h"
#include "c++/methods/callbacks/TagsInstanceCallbacks.h"
#include "c++/methods/callbacks/GameInstanceCallbacks.h"
#include "c/methods/callbacks/../../../wrappers/MinizipWrapper.h"
#include "Utility.h"

namespace modio
{
Instance::Instance(u32 environment, u32 game_id, const std::string &api_key)
{
  current_call_id = 0;
  modioInit(environment, game_id, false, false, api_key.c_str(), NULL);
}

Instance::Instance(u32 environment, u32 game_id, bool retrieve_mods_from_other_games, bool polling_enabled, const std::string &api_key, const std::string &root_path)
{
  current_call_id = 0;
  modioInit(environment, game_id, retrieve_mods_from_other_games, polling_enabled, api_key.c_str(), root_path.c_str());
}

Instance::~Instance()
{
  modio::writeLogLine("mod.io C++ interface is shutting down", MODIO_DEBUGLEVEL_LOG);
  
  modioShutdown();

  if(set_download_listener_call)
    delete set_download_listener_call;
  if(set_upload_listener_call)
    delete set_upload_listener_call;

  clearAuthenticationRequestCalls();
  clearCommentsRequestCalls();
  clearDependenciesRequestCalls();
  clearImageRequestCalls();
  clearMediaRequestCalls();
  clearMeRequestCalls();
  clearMetadataKVPRequestCalls();
  clearModEventsRequestCalls();
  clearModfileRequestCalls();
  clearModRequestCalls();
  clearGameRequestCalls();
  clearModStatsRequestCalls();
  clearRatingsRequestCalls();
  clearReportsRequestCalls();
  clearSubscriptionRequestCalls();
  clearTagsRequestCalls();

  modio::writeLogLine("mod.io C++ interface finished shutting down", MODIO_DEBUGLEVEL_LOG);
}

void Instance::setDebugLevel(u32 debug_level)
{
  modioSetDebugLevel(debug_level);
}

void Instance::setModEventsPollInterval(u32 interval_in_seconds)
{
  modioSetModEventsPollInterval(interval_in_seconds);
}

void Instance::setUserEventsPollInterval(u32 interval_in_seconds)
{
  modioSetUserEventsPollInterval(interval_in_seconds);
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

void Instance::pollEvents()
{
  modioPollEvents();
}
} // namespace modio
