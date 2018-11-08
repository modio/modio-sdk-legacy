#include "c++/ModIOInstance.h"

namespace modio
{
std::map<u32, GenericCall *> submit_report_calls;

void onSubmitReport(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  submit_report_calls[call_id]->callback((const Response &)response);

  delete (u32 *)object;
  delete submit_report_calls[call_id];
  submit_report_calls.erase(call_id);
}

void clearReportsRequestCalls()
{
  for (auto submit_report_call : submit_report_calls)
    delete submit_report_call.second;
  submit_report_calls.clear();
}
} // namespace modio
