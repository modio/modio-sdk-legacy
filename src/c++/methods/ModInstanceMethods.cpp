#include "c++/ModIOInstance.h"

namespace modio
{
  void Instance::getMod(u32 mod_id, const std::function<void(const modio::Response& response, const modio::Mod& mod)>& callback)
  {
    const struct GetModCall* get_mod_call = new GetModCall{callback};
    get_mod_calls[this->current_call_id] = (GetModCall*)get_mod_call;

    modioGetMod((void*)new u32(this->current_call_id), mod_id, &onGetMod);

    this->current_call_id++;
  }

  void Instance::getAllMods(modio::FilterCreator& filter, const std::function<void(const modio::Response&, const std::vector<modio::Mod> & mods)>& callback)
  {
    const struct GetAllModsCall* get_mods_call = new GetAllModsCall{callback};
    get_all_mods_calls[this->current_call_id] = (GetAllModsCall*)get_mods_call;

    modioGetAllMods((void*)new u32(this->current_call_id), *filter.getFilter(), &onGetAllMods);

    this->current_call_id++;
  }

  void Instance::addMod(modio::ModCreator& mod_handler, const std::function<void(const modio::Response& response, const modio::Mod& mod)>& callback)
  {
    const struct AddModCall* add_mod_call = new AddModCall{callback};
    add_mod_calls[this->current_call_id] = (AddModCall*)add_mod_call;

    modioAddMod((void*)new u32(this->current_call_id), *mod_handler.getModioModCreator(), &onAddMod);

    this->current_call_id++;
  }

  void Instance::editMod(u32 mod_id, modio::ModEditor& mod_handler, const std::function<void(const modio::Response& response, const modio::Mod& mod)>& callback)
  {
    const struct EditModCall* edit_mod_call = new EditModCall{callback};
    edit_mod_calls[this->current_call_id] = (EditModCall*)edit_mod_call;

    modioEditMod((void*)new u32(this->current_call_id), mod_id, *mod_handler.getModioModEditor(), &onEditMod);

    this->current_call_id++;
  }

  void Instance::deleteMod(u32 mod_id, const std::function<void(const modio::Response& response)>& callback)
  {
    const struct DeleteModCall* delete_mod_call = new DeleteModCall{callback};
    delete_mod_calls[this->current_call_id] = (DeleteModCall*)delete_mod_call;

    modioDeleteMod((void*)new u32(this->current_call_id), mod_id, &onDeleteMod);

    this->current_call_id++;
  }
}
