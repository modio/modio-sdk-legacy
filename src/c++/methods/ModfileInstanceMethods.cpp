#include "c++/ModIOInstance.h"

namespace modio
{
void Instance::getModfile(u32 mod_id, u32 modfile_id, const std::function<void(const modio::Response &response, const modio::Modfile &modfile)> &callback)
{
  const struct GetModfileCall *get_modfile_call = new GetModfileCall{callback};
  get_modfile_calls[this->current_call_id] = (GetModfileCall *)get_modfile_call;

  modioGetModfile((void *)new u32(this->current_call_id), mod_id, modfile_id, &onGetModfile);

  this->current_call_id++;
}

void Instance::getAllModfiles(u32 mod_id, modio::FilterCreator &filter, const std::function<void(const modio::Response &, const std::vector<modio::Modfile> &modfiles)> &callback)
{
  const struct GetAllModfilesCall *get_all_modfiles_call = new GetAllModfilesCall{callback};
  get_all_modfiles_calls[this->current_call_id] = (GetAllModfilesCall *)get_all_modfiles_call;

  modioGetAllModfiles((void *)new u32(this->current_call_id), mod_id, *filter.getFilter(), &onGetAllModfiles);

  this->current_call_id++;
}

void Instance::addModfile(u32 mod_id, modio::ModfileCreator &modfile_handler)
{
  modioAddModfile(mod_id, *modfile_handler.getModioModfileCreator());
}

void Instance::editModfile(u32 mod_id, u32 modfile_id, modio::ModfileEditor &modfile_handler, const std::function<void(const modio::Response &response, const modio::Modfile &modfile)> &callback)
{
  const struct EditModfileCall *edit_modfile_call = new EditModfileCall{callback};
  edit_modfile_calls[this->current_call_id] = (EditModfileCall *)edit_modfile_call;

  modioEditModfile((void *)new u32(this->current_call_id), mod_id, modfile_id, *modfile_handler.getModioModfileEditor(), &onEditModfile);

  this->current_call_id++;
}

void Instance::deleteModfile(u32 mod_id, u32 modfile_id, const std::function<void(const modio::Response &response)> &callback)
{
  const struct GenericCall *delete_modfile_call = new GenericCall{callback};
  delete_modfile_calls[this->current_call_id] = (GenericCall *)delete_modfile_call;

  modioDeleteModfile((void *)new u32(this->current_call_id), mod_id, modfile_id, &onDeleteModfile);

  this->current_call_id++;
}
} // namespace modio
