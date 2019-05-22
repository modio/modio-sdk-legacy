#include "c/methods/ReportsMethods.h"

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
