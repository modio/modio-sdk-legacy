#include "c++/ModIOInstance.h"
#include "ModioUtility.h"
#include "c++/methods/callbacks/ReportsInstanceCallbacks.h"

namespace modio
{
    void Instance::submitReport(std::string resource, u32 id, u32 type, std::string name, std::string summary, const std::function<void(const modio::Response &response)> &callback)
    {
		struct GenericCall* submit_report_call = new GenericCall{ callback };
		submit_report_calls[current_call_id] = submit_report_call;

		modioSubmitReport((void*)((uintptr_t)current_call_id), resource.c_str(), id, type, name.c_str(), summary.c_str(), &onSubmitReport);

		current_call_id++;
	}
}
