#include "c/methods/DependenciesMethods.h"

extern "C"
{
	void modioGetAllModDependencies(void* object, u32 mod_id, void(*callback)(void* object, ModioResponse response, ModioDependency* dependencies_array, u32 dependencies_array_size))
	{
		std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/dependencies/?api_key=" + modio::API_KEY;
		u32 call_number = modio::curlwrapper::getCallNumber();

		get_all_mod_dependencies_callbacks[call_number] = new GetAllModDependenciesParams;
		get_all_mod_dependencies_callbacks[call_number]->callback = callback;
		get_all_mod_dependencies_callbacks[call_number]->object = object;

		modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetAllModDependencies);
	}

	void modioAddModDependencies(void* object, u32 mod_id, u32* dependencies_array, u32 dependencies_array_size, void(*callback)(void* object, ModioResponse response))
	{
		std::map<std::string, std::string> data;

		u32 call_number = modio::curlwrapper::getCallNumber();

		add_mod_dependencies_callbacks[call_number] = new GenericRequestParams;
		add_mod_dependencies_callbacks[call_number]->callback = callback;
		add_mod_dependencies_callbacks[call_number]->object = object;

		std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/dependencies";

		for (u32 i = 0; i<dependencies_array_size; i++)
		{
			if (i == 0)
				url += "?";
			else
				url += "&";
			url += std::string("dependencies[]=") + modio::toString(dependencies_array[i]);
		}

		modio::curlwrapper::post(call_number, url, modio::getUrlEncodedHeaders(), data, &modioOnAddModDependencies);
	}

	void modioDeleteModDependencies(void* object, u32 mod_id, u32* dependencies_array, u32 dependencies_array_size, void(*callback)(void* object, ModioResponse response))
	{
		std::map<std::string, std::string> data;
		u32 call_number = modio::curlwrapper::getCallNumber();

		delete_mod_dependencies_callbacks[call_number] = new GenericRequestParams;
		delete_mod_dependencies_callbacks[call_number]->callback = callback;
		delete_mod_dependencies_callbacks[call_number]->object = object;

		std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/dependencies";

		for (u32 i = 0; i<dependencies_array_size; i++)
		{
			if (i == 0)
				url += "?";
			else
				url += "&";
			url += std::string("dependencies[]=") + modio::toString(dependencies_array[i]);
		}

		modio::curlwrapper::deleteCall(call_number, url, modio::getUrlEncodedHeaders(), data, &modioOnDeleteModDependencies);
	}
}
