#include "c/schemas/ModioDependency.h"
#include "Utility.h"                // for hasKey
#include "c/ModioC.h"               // for ModioDependency

extern "C"
{
  void modioInitDependency(ModioDependency* dependency, nlohmann::json dependency_json)
  {
    dependency->mod_id = 0;
    if(modio::hasKey(dependency_json, "mod_id"))
      dependency->mod_id = dependency_json["mod_id"];

    dependency->date_added = 0;
    if(modio::hasKey(dependency_json, "date_added"))
      dependency->date_added = dependency_json["date_added"];
  }

  void modioInitDependencyCpp(ModioDependency* modio_dependency, modio::Dependency* dependency)
  {
    modio_dependency->mod_id = dependency->mod_id;
    modio_dependency->date_added = dependency->date_added;
  }

  void modioFreeDependency(ModioDependency* dependency)
  {
    if(dependency)
    {
      //No pointers
    }
  }
}
