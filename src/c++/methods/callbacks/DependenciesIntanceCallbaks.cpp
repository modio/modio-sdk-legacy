#include "c++/ModIOInstance.h"

namespace modio
{
std::map<u32, GetAllModDependenciesCall *> get_all_mod_dependencies_calls;
std::map<u32, AddModDependenciesCall *> add_mod_dependencies_calls;
std::map<u32, DeleteModDependenciesCall *> delete_mod_dependencies_calls;

void onGetAllModDependencies(void *object, ModioResponse modio_response, ModioDependency *dependencies_array, u32 dependencies_array_size)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::Dependency> dependencies_vector;
  dependencies_vector.resize(dependencies_array_size);
  for (u32 i = 0; i < dependencies_array_size; i++)
  {
    dependencies_vector[i].initialize(dependencies_array[i]);
  }

  get_all_mod_dependencies_calls[call_id]->callback((const Response &)response, dependencies_vector);

  delete (u32 *)object;
  delete get_all_mod_dependencies_calls[call_id];
  get_all_mod_dependencies_calls.erase(call_id);
}

void onAddModDependencies(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  add_mod_dependencies_calls[call_id]->callback((const Response &)response);

  delete (u32 *)object;
  delete add_mod_dependencies_calls[call_id];
  add_mod_dependencies_calls.erase(call_id);
}

void onDeleteModDependencies(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  delete_mod_dependencies_calls[call_id]->callback((const Response &)response);

  delete (u32 *)object;
  delete delete_mod_dependencies_calls[call_id];
  delete_mod_dependencies_calls.erase(call_id);
}

void clearDependenciesRequestCalls()
{
  for (auto get_all_mod_dependencies_call : get_all_mod_dependencies_calls)
    delete get_all_mod_dependencies_call.second;
  get_all_mod_dependencies_calls.clear();

  for (auto add_mod_dependencies_call : add_mod_dependencies_calls)
    delete add_mod_dependencies_call.second;
  add_mod_dependencies_calls.clear();

  for (auto delete_mod_dependencies_call : delete_mod_dependencies_calls)
    delete delete_mod_dependencies_call.second;
  delete_mod_dependencies_calls.clear();
}

} // namespace modio
