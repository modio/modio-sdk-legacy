#include "c++/schemas/InstalledMod.h"

namespace modio
{
	void InstalledMod::initialize(ModioInstalledMod modio_installed_mod)
	{
		this->mod_id = modio_installed_mod.mod_id;
		this->modfile_id = modio_installed_mod.modfile_id;
		this->updated_at = modio_installed_mod.updated_at;
		if (modio_installed_mod.path)
			this->path = modio_installed_mod.path;
		this->mod.initialize(modio_installed_mod.mod);
	}

	nlohmann::json InstalledMod::toJson()
	{
		nlohmann::json installed_mod_json;

		installed_mod_json["mod_id"] = this->mod_id;
		installed_mod_json["modfile_id"] = this->modfile_id;
		installed_mod_json["updated_at"] = this->updated_at;
		installed_mod_json["path"] = this->path;

		return installed_mod_json;
	}
}
