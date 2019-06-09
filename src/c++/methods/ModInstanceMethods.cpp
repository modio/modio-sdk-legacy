#include "c++/ModIOInstance.h"

namespace modio
{
void Instance::getMod(u32 mod_id, const std::function<void(const modio::Response &response, const modio::Mod &mod)> &callback)
{
  struct GetModCall *get_mod_call = new GetModCall{callback};
  get_mod_calls[current_call_id] = get_mod_call;

  modioGetMod(new u32(current_call_id), mod_id, &onGetMod);

  current_call_id++;
}

void Instance::getAllMods(modio::FilterCreator &filter, const std::function<void(const modio::Response &, const std::vector<modio::Mod> &mods)> &callback)
{
  struct GetAllModsCall *get_mods_call = new GetAllModsCall{callback};
  get_all_mods_calls[current_call_id] = get_mods_call;

  modioGetAllMods(new u32(current_call_id), *filter.getFilter(), &onGetAllMods);

  current_call_id++;
}

void Instance::addMod(modio::ModCreator &mod_handler, const std::function<void(const modio::Response &response, const modio::Mod &mod)> &callback)
{
  struct AddModCall *add_mod_call = new AddModCall{callback};
  add_mod_calls[current_call_id] = add_mod_call;

  modioAddMod(new u32(current_call_id), *mod_handler.getModioModCreator(), &onAddMod);

  current_call_id++;
}

void Instance::editMod(u32 mod_id, modio::ModEditor &mod_handler, const std::function<void(const modio::Response &response, const modio::Mod &mod)> &callback)
{
  struct EditModCall *edit_mod_call = new EditModCall{callback};
  edit_mod_calls[current_call_id] = edit_mod_call;

  modioEditMod(new u32(current_call_id), mod_id, *mod_handler.getModioModEditor(), &onEditMod);

  current_call_id++;
}

void Instance::deleteMod(u32 mod_id, const std::function<void(const modio::Response &response)> &callback)
{
  struct GenericCall *delete_mod_call = new GenericCall{callback};
  delete_mod_calls[current_call_id] = delete_mod_call;

  modioDeleteMod(new u32(current_call_id), mod_id, &onDeleteMod);

  current_call_id++;
}
} // namespace modio
