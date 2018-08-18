#include "c/methods/callbacks/DependenciesCallbacks.h"

std::map< u32, GetAllModDependenciesParams* > get_all_mod_dependencies_callbacks;
std::map< u32, AddModDependienciesParams* > add_mod_dependencies_callbacks;
std::map< u32, DeleteModDependenciesParams* > delete_mod_dependencies_callbacks;

void modioOnGetAllModDependencies(u32 call_number, u32 response_code, nlohmann::json response_json)
{
	ModioResponse response;
	modioInitResponse(&response, response_json);
	response.code = response_code;

	ModioDependency* dependencies_array = NULL;
	u32 dependencies_array_size = 0;
	if (response.code == 200)
	{
		try
		{
			if (modio::hasKey(response_json, "data"))
			{
				dependencies_array_size = (u32)response_json["data"].size();
				dependencies_array = new ModioDependency[dependencies_array_size];
				for (u32 i = 0; i<dependencies_array_size; i++)
				{
					modioInitDependency(&(dependencies_array[i]), response_json["data"][i]);
				}
			}
		}
		catch (nlohmann::json::parse_error &e)
		{
			modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
		}
	}
	get_all_mod_dependencies_callbacks[call_number]->callback(get_all_mod_dependencies_callbacks[call_number]->object, response, dependencies_array, dependencies_array_size);
	for (u32 i = 0; i<dependencies_array_size; i++)
	{
		modioFreeDependency(&(dependencies_array[i]));
	}
	if (dependencies_array)
		delete[] dependencies_array;
	delete get_all_mod_dependencies_callbacks[call_number];
	get_all_mod_dependencies_callbacks.erase(call_number);
}

void modioOnAddModDependencies(u32 call_number, u32 response_code, nlohmann::json response_json)
{
	ModioResponse response;
	modioInitResponse(&response, response_json);
	response.code = response_code;
	add_mod_dependencies_callbacks[call_number]->callback(add_mod_dependencies_callbacks[call_number]->object, response);
	
	delete add_mod_dependencies_callbacks[call_number];
	add_mod_dependencies_callbacks.erase(call_number);
}

void modioOnDeleteModDependencies(u32 call_number, u32 response_code, nlohmann::json response_json)
{
	ModioResponse response;
	modioInitResponse(&response, response_json);
	response.code = response_code;

	delete_mod_dependencies_callbacks[call_number]->callback(delete_mod_dependencies_callbacks[call_number]->object, response);

	delete delete_mod_dependencies_callbacks[call_number];
	delete_mod_dependencies_callbacks.erase(call_number);
}
