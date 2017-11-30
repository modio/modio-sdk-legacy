#include "ModIOInstance.h"

namespace modio
{
  struct GetModsCall
  {
    const std::function<void(const modio::Response&, std::vector<modio::Mod>& mods)> callback;
  };

  struct AddModCall
  {
    const std::function<void(const modio::Response& response, const modio::Mod& mod)> callback;
  };

  struct EditModCall
  {
    const std::function<void(const modio::Response& response, const modio::Mod& mod)> callback;
  };

  struct DeleteModCall
  {
    const std::function<void(const modio::Response& response, u32 mod_id)> callback;
  };

  std::map<int, GetModsCall*> get_mods_calls;
  std::map<int, AddModCall*> add_mod_calls;
  std::map<int, EditModCall*> edit_mod_calls;
  std::map<int, DeleteModCall*> delete_mod_calls;

  void onGetMods(void* object, ModioResponse modio_response, ModioMod* mods, int mods_size)
  {
    int call_id = *((int*)object);

    modio::Response response;
    response.initialize(modio_response);

    std::vector<modio::Mod> mods_vector;
    mods_vector.resize(mods_size);
    for(int i=0; i < mods_size; i++)
    {
      mods_vector[i].initialize(mods[i]);
      delete &mods[i];
    }

    get_mods_calls[call_id]->callback((const Response&)response, mods_vector);

    delete (int*)object;
    delete get_mods_calls[call_id];
    get_mods_calls.erase(call_id);
  }

  void onAddMod(void* object, ModioResponse modio_response, ModioMod* mod)
  {
    int call_id = *((int*)object);

    modio::Response response;
    response.initialize(modio_response);

    modio::Mod modio_mod;
    add_mod_calls[call_id]->callback((const Response&)response, modio_mod);

    delete (int*)object;
    delete add_mod_calls[call_id];
    add_mod_calls.erase(call_id);
  }

  void onEditMod(void* object, ModioResponse modio_response, ModioMod* mod)
  {
    int call_id = *((int*)object);

    modio::Response response;
    response.initialize(modio_response);

    modio::Mod modio_mod;
    edit_mod_calls[call_id]->callback((const Response&)response, modio_mod);

    delete (int*)object;
    delete edit_mod_calls[call_id];
    edit_mod_calls.erase(call_id);
  }

  void onDeleteMod(void* object, ModioResponse modio_response, int mod_id)
  {
    int call_id = *((int*)object);

    modio::Response response;
    response.initialize(modio_response);

    delete_mod_calls[call_id]->callback((const modio::Response&)response, mod_id);

    delete (int*)object;
    delete delete_mod_calls[call_id];
    delete_mod_calls.erase(call_id);
  }

  bool Instance::getMods(modio::Filter& filter, const std::function<void(const modio::Response&, const std::vector<modio::Mod> & mods)>& callback)
  {
    const struct GetModsCall* get_mods_call = new GetModsCall{callback};
    get_mods_calls[this->current_call_id] = (GetModsCall*)get_mods_call;

    modioGetMods((void*)new int(this->current_call_id), filter.getFilter(), &onGetMods);

    this->current_call_id++;
    return true;
  }

  void Instance::addMod(modio::ModHandler& mod_handler, const std::function<void(const modio::Response& response, const modio::Mod& mod)>& callback)
  {
    const struct AddModCall* add_mod_call = new AddModCall{callback};
    add_mod_calls[this->current_call_id] = (AddModCall*)add_mod_call;

    modioAddMod((void*)new int(this->current_call_id), mod_handler.getModioModHandler(), &onAddMod);

    this->current_call_id++;
  }

  void Instance::editMod(u32 mod_id, modio::ModHandler& mod_handler, const std::function<void(const modio::Response& response, const modio::Mod& mod)>& callback)
  {
    const struct EditModCall* edit_mod_call = new EditModCall{callback};
    edit_mod_calls[this->current_call_id] = (EditModCall*)edit_mod_call;

    modioEditMod((void*)new int(this->current_call_id), mod_id, mod_handler.getModioModHandler(), &onEditMod);

    this->current_call_id++;
  }

  void Instance::deleteMod(u32 mod_id, const std::function<void(const modio::Response& response, u32 mod_id)>& callback)
  {
    const struct DeleteModCall* delete_mod_call = new DeleteModCall{callback};
    delete_mod_calls[this->current_call_id] = (DeleteModCall*)delete_mod_call;

    modioDeleteMod((void*)new int(this->current_call_id), mod_id, &onDeleteMod);

    this->current_call_id++;
  }
}
