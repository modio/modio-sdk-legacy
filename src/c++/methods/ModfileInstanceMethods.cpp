#include "c++/ModIOInstance.h"
#include "ModioUtility.h"
#include "c++/methods/callbacks/ModfileInstanceCallbacks.h"
#include "c++/creators/FilterCreator.h"
#include "c++/creators/ModfileCreator.h"
#include "c++/creators/ModfileEditor.h"

namespace modio
{
void Instance::getModfile(u32 mod_id, u32 modfile_id, const std::function<void(const modio::Response &response, const modio::Modfile &modfile)> &callback)
{
  struct GetModfileCall *get_modfile_call = new GetModfileCall{callback};
  get_modfile_calls[current_call_id] = get_modfile_call;

  modioGetModfile((void*)((uintptr_t)current_call_id), mod_id, modfile_id, &onGetModfile);

  current_call_id++;
}

void Instance::getAllModfiles(u32 mod_id, modio::FilterCreator &filter, const std::function<void(const modio::Response &, const std::vector<modio::Modfile> &modfiles)> &callback)
{
  struct GetAllModfilesCall *get_all_modfiles_call = new GetAllModfilesCall{callback};
  get_all_modfiles_calls[current_call_id] = get_all_modfiles_call;

  modioGetAllModfiles((void*)((uintptr_t)current_call_id), mod_id, *filter.getFilter(), &onGetAllModfiles);

  current_call_id++;
}

void Instance::addModfile(u32 mod_id, modio::ModfileCreator &modfile_handler)
{
  modioAddModfile(mod_id, *modfile_handler.getModioModfileCreator());
}

void Instance::editModfile(u32 mod_id, u32 modfile_id, modio::ModfileEditor &modfile_handler, const std::function<void(const modio::Response &response, const modio::Modfile &modfile)> &callback)
{
  struct EditModfileCall *edit_modfile_call = new EditModfileCall{callback};
  edit_modfile_calls[current_call_id] = edit_modfile_call;

  modioEditModfile((void*)((uintptr_t)current_call_id), mod_id, modfile_id, *modfile_handler.getModioModfileEditor(), &onEditModfile);

  current_call_id++;
}

void Instance::deleteModfile(u32 mod_id, u32 modfile_id, const std::function<void(const modio::Response &response)> &callback)
{
  struct GenericCall *delete_modfile_call = new GenericCall{callback};
  delete_modfile_calls[current_call_id] = delete_modfile_call;

  modioDeleteModfile((void*)((uintptr_t)current_call_id), mod_id, modfile_id, &onDeleteModfile);

  current_call_id++;
}
} // namespace modio
