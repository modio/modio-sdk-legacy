#include "c++/ModIOInstance.h"

namespace modio
{
    void Instance::submitReport(std::string resource, u32 id, u32 type, std::string name, std::string summary, const std::function<void(const modio::Response &response)> &callback)
    {
		const struct GenericCall* submit_report_call = new GenericCall{ callback };
		submit_report_calls[current_call_id] = (GenericCall*)submit_report_call;

		modioSubmitReport((void*)new u32(current_call_id), resource.c_str(), id, type, name.c_str(), summary.c_str(), &onSubmitReport);

		current_call_id++;
	}
}
