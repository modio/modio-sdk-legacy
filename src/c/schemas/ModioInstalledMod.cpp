#include "c/schemas/ModioInstalledMod.h"

extern "C"
{
	void modioInitInstalledMod(ModioInstalledMod* installed_mod, nlohmann::json installed_mod_json)
	{
		installed_mod->mod_id = 0;
		if (modio::hasKey(installed_mod_json, "mod_id"))
			installed_mod->mod_id = installed_mod_json["mod_id"];

		installed_mod->modfile_id = 0;
		if (modio::hasKey(installed_mod_json, "modfile_id"))
			installed_mod->modfile_id = installed_mod_json["modfile_id"];

		installed_mod->updated_at = 0;
		if (modio::hasKey(installed_mod_json, "updated_at"))
			installed_mod->updated_at = installed_mod_json["updated_at"];

		installed_mod->path = NULL;
		if (modio::hasKey(installed_mod_json, "path"))
		{
			std::string path_str = installed_mod_json["path"];
			installed_mod->path = new char[path_str.size() + 1];
			strcpy(installed_mod->path, path_str.c_str());
		}

		nlohmann::json mod_cache_json = modio::openJson(modio::addSlashIfNeeded(installed_mod->path) + "modio.json");
		modioInitMod(&(installed_mod->mod), mod_cache_json);
	}

	void modioFreeInstalledMod(ModioInstalledMod* installed_mod)
	{
		if (installed_mod)
		{
			if (installed_mod->path)
				delete[] installed_mod->path;
		}
	}
}
