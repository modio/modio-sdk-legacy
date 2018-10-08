#include "c++/schemas/Dependency.h"

namespace modio
{
void Dependency::initialize(ModioDependency modio_dependency)
{
	this->mod_id = modio_dependency.mod_id;
	this->date_added = modio_dependency.date_added;
}

nlohmann::json toJson(Dependency &dependency)
{
	nlohmann::json dependency_json;

	dependency_json["mod_id"] = dependency.mod_id;
	dependency_json["date_added"] = dependency.date_added;

	return dependency_json;
}
} // namespace modio
