#include "c/methods/callbacks/DependenciesCallbacks.h"

std::map<u32, GetAllModDependenciesParams *> get_all_mod_dependencies_callbacks;
std::map<u32, GenericRequestParams *> add_mod_dependencies_callbacks;
std::map<u32, GenericRequestParams *> delete_mod_dependencies_callbacks;

void modioOnGetAllModDependencies(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;
  ModioDependency *dependencies_array = NULL;
  u32 dependencies_array_size = 0;

  if (response.code == 200)
  {
    if (modio::hasKey(response_json, "data"))
    {
      dependencies_array_size = (u32)response_json["data"].size();
      dependencies_array = new ModioDependency[dependencies_array_size];
      for (u32 i = 0; i < dependencies_array_size; i++)
      {
        modioInitDependency(&(dependencies_array[i]), response_json["data"][i]);
      }
    }
    else
    {
      modio::writeLogLine("Could not retreive data array from API.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  get_all_mod_dependencies_callbacks[call_number]->callback(get_all_mod_dependencies_callbacks[call_number]->object, response, dependencies_array, dependencies_array_size);

  delete get_all_mod_dependencies_callbacks[call_number];
  get_all_mod_dependencies_callbacks.erase(call_number);

  modioFreeResponse(&response);
  for (u32 i = 0; i < dependencies_array_size; i++)
    modioFreeDependency(&(dependencies_array[i]));
  if (dependencies_array)
    delete[] dependencies_array;
}

void modioOnAddModDependencies(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  add_mod_dependencies_callbacks[call_number]->callback(add_mod_dependencies_callbacks[call_number]->object, response);

  delete add_mod_dependencies_callbacks[call_number];
  add_mod_dependencies_callbacks.erase(call_number);

  modioFreeResponse(&response);
}

void modioOnDeleteModDependencies(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  delete_mod_dependencies_callbacks[call_number]->callback(delete_mod_dependencies_callbacks[call_number]->object, response);

  delete delete_mod_dependencies_callbacks[call_number];
  delete_mod_dependencies_callbacks.erase(call_number);

  modioFreeResponse(&response);
}

void clearDependenciesCallbackParams()
{
  for (auto get_all_mod_dependencies_callback : get_all_mod_dependencies_callbacks)
    delete get_all_mod_dependencies_callback.second;
  get_all_mod_dependencies_callbacks.clear();

  for (auto add_mod_dependencies_callback : add_mod_dependencies_callbacks)
    delete add_mod_dependencies_callback.second;
  add_mod_dependencies_callbacks.clear();

  for (auto delete_mod_dependencies_callback : delete_mod_dependencies_callbacks)
    delete delete_mod_dependencies_callback.second;
  delete_mod_dependencies_callbacks.clear();
}