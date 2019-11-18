#include <map>                                            // for map
#include <string>                                         // for string, all...
#include "Utility.h"          // for toString
#include "wrappers/CurlWrapper.h"         // for getCallNumber
#include "Globals.h"         // for MODIO_URL
#include "ModioUtility.h"    // for GenericRequ...
#include "c/ModioC.h"  // for u32, ModioR...
#include "c/methods/callbacks/ReportsCallbacks.h"         // for submit_repo...
#include "dependencies/nlohmann/json.hpp"                 // for json

extern "C" {

  void modioSubmitReport(void* object, char const* resource, u32 id, u32 type, char const* name, char const* summary, void(*callback)(void* object, ModioResponse response))
  {
    std::map<std::string, std::string> data;
    u32 call_number = modio::curlwrapper::getCallNumber();

    submit_report_callbacks[call_number] = new GenericRequestParams;
    submit_report_callbacks[call_number]->callback = callback;
    submit_report_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "report?resource=" + resource + "&id=" + modio::toString(id) + "&type=" + modio::toString(type) + "&name=" + name + "&summary=" + summary;

    modio::curlwrapper::post(call_number, url, modio::getUrlEncodedHeaders(), data, &modioOnSubmitReport);
  }
}
