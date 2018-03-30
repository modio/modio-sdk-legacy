#include "c++/ModIOInstance.h"

namespace modio
{
	std::map<u32, SubmitReportCall*> submit_report_calls;

	void onSubmitReport(void* object, ModioResponse modio_response)
	{
		u32 call_id = *((u32*)object);

		modio::Response response;
		response.initialize(modio_response);

		submit_report_calls[call_id]->callback((const Response&)response);

		delete (u32*)object;
		delete submit_report_calls[call_id];
		submit_report_calls.erase(call_id);
	}
}
