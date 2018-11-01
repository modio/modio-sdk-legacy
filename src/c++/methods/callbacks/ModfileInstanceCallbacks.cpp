#include "c++/ModIOInstance.h"

namespace modio
{
std::map<u32, GetModfileCall *> get_modfile_calls;
std::map<u32, GetAllModfilesCall *> get_all_modfiles_calls;
std::map<u32, AddModfileCall *> add_modfile_calls;
std::map<u32, EditModfileCall *> edit_modfile_calls;
std::map<u32, GenericCall *> delete_modfile_calls;

void onGetModfile(void *object, ModioResponse modio_response, ModioModfile modfile)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  modio::Modfile modio_modfile;
  if (modio_response.code == 200)
  {
    modio_modfile.initialize(modfile);
  }

  get_modfile_calls[call_id]->callback((const Response &)response, modio_modfile);

  delete (u32 *)object;
  delete get_modfile_calls[call_id];
  get_modfile_calls.erase(call_id);
}

void onGetAllModfiles(void *object, ModioResponse modio_response, ModioModfile modfiles[], u32 modfiles_size)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::Modfile> modfiles_vector;
  modfiles_vector.resize(modfiles_size);
  for (u32 i = 0; i < modfiles_size; i++)
  {
    modfiles_vector[i].initialize(modfiles[i]);
  }

  get_all_modfiles_calls[call_id]->callback((const Response &)response, modfiles_vector);

  delete (u32 *)object;
  delete get_all_modfiles_calls[call_id];
  get_all_modfiles_calls.erase(call_id);
}

void onAddModfile(void *object, ModioResponse modio_response, ModioModfile modio_modfile)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  modio::Modfile modfile;
  modfile.initialize(modio_modfile);

  add_modfile_calls[call_id]->callback(response, modfile);

  delete (u32 *)object;
  delete add_modfile_calls[call_id];
  add_modfile_calls.erase(call_id);
}

void onEditModfile(void *object, ModioResponse modio_response, ModioModfile modio_modfile)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  modio::Modfile modfile;
  modfile.initialize(modio_modfile);

  edit_modfile_calls[call_id]->callback(response, modfile);
  delete (u32 *)object;
  delete edit_modfile_calls[call_id];
  edit_modfile_calls.erase(call_id);
}

void onDeleteModfile(void *object, ModioResponse modio_response)
{
  u32 call_id = *((u32 *)object);

  modio::Response response;
  response.initialize(modio_response);

  delete_modfile_calls[call_id]->callback(response);
  delete (u32 *)object;
  delete delete_modfile_calls[call_id];
  delete_modfile_calls.erase(call_id);
}

void clearModfileRequestCalls()
{
  for (auto get_modfile_call : get_modfile_calls)
    delete get_modfile_call.second;
  get_modfile_calls.clear();

  for (auto get_all_modfiles_call : get_all_modfiles_calls)
    delete get_all_modfiles_call.second;
  get_all_modfiles_calls.clear();

  for (auto add_modfile_call : add_modfile_calls)
    delete add_modfile_call.second;
  add_modfile_calls.clear();

  for (auto edit_modfile_call : edit_modfile_calls)
    delete edit_modfile_call.second;
  edit_modfile_calls.clear();

  for (auto delete_modfile_call : delete_modfile_calls)
    delete delete_modfile_call.second;
  delete_modfile_calls.clear();
}
} // namespace modio
