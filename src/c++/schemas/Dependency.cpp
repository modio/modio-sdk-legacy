#include "c++/schemas/Dependency.h"

namespace modio
{
	void Dependency::initialize(ModioDependency modio_dependency)
	{
		this->mod_id = modio_dependency.mod_id;
		this->date_added = modio_dependency.date_added;
	}

	nlohmann::json Dependency::toJson()
	{
		nlohmann::json dependency_json;

		dependency_json["mod_id"] = this->mod_id;
		dependency_json["date_added"] = this->date_added;

		return dependency_json;
	}
}
