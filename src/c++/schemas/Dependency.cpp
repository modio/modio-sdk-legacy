#include "c++/schemas/Dependency.h"
#include "c/ModioC.h"                      // for ModioDependency
#include "dependencies/nlohmann/json.hpp"  // for json

namespace modio
{
void Dependency::initialize(ModioDependency modio_dependency)
{
	mod_id = modio_dependency.mod_id;
	date_added = modio_dependency.date_added;
}

nlohmann::json toJson(Dependency &dependency)
{
	nlohmann::json dependency_json;

	dependency_json["mod_id"] = dependency.mod_id;
	dependency_json["date_added"] = dependency.date_added;

	return dependency_json;
}
} // namespace modio
