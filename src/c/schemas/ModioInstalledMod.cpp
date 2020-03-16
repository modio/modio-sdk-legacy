#include "c/schemas/ModioInstalledMod.h"
#include "Utility.h"                // for hasKey
#include "c/ModioC.h"               // for ModioDownload
#include "c/schemas/ModioMod.h" 	// for modioInitMod ...

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

		installed_mod->date_updated = 0;
		if (modio::hasKey(installed_mod_json, "date_updated"))
			installed_mod->date_updated = installed_mod_json["date_updated"];

		installed_mod->path = NULL;
		if (modio::hasKey(installed_mod_json, "path"))
		{
			std::string path_str = installed_mod_json["path"];
			installed_mod->path = new char[path_str.size() + 1];
			strcpy(installed_mod->path, path_str.c_str());
		}

		nlohmann::json mod_cache_json;
		if(installed_mod->path)
		{
			std::string modio_json_path = modio::addSlashIfNeeded(installed_mod->path) + "modio.json";
			if(modio::fileExists(modio_json_path))
			{
				mod_cache_json = modio::openJson(modio::addSlashIfNeeded(installed_mod->path) + "modio.json");
			}
		}
		modioInitMod(&(installed_mod->mod), mod_cache_json);
	}

  void modioInitInstalledModCpp(ModioInstalledMod* modio_installed_mod, modio::InstalledMod* installed_mod)
  {
    modio_installed_mod->mod_id = installed_mod->mod_id;
    modio_installed_mod->modfile_id = installed_mod->modfile_id;
    modio_installed_mod->date_updated = installed_mod->date_updated;

    modio_installed_mod->path = new char[installed_mod->path.size() + 1];
    strcpy(modio_installed_mod->path, installed_mod->path.c_str());

    modioInitModCpp(&(modio_installed_mod->mod), &(installed_mod->mod));
  }

	void modioFreeInstalledMod(ModioInstalledMod* installed_mod)
	{
		if (installed_mod)
		{
			if (installed_mod->path)
				delete[] installed_mod->path;

			modioFreeMod(&installed_mod->mod);
		}
	}
}
