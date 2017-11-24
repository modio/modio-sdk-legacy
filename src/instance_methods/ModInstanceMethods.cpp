#include "ModIOInstance.h"

namespace modio
{
  struct GetModsCall
  {
    void* object;
    const std::function<void(void* object, const ModioResponse&, std::vector<ModioMod*> mods)> callback;
  };

  struct EditModCall
  {
    void* object;
    const std::function<void(void* object, const ModioResponse& response, const ModioMod& mod)> callback;
  };

  struct DeleteModCall
  {
    void* object;
    const std::function<void(void* object, const ModioResponse& response, const ModioMod& mod)> callback;
  };

  std::map<int, GetModsCall*> get_mods_calls;
  std::map<int, EditModCall*> edit_mod_calls;
  std::map<int, DeleteModCall*> delete_mod_calls;

  void onGetMods(void* object, ModioResponse response, ModioMod* mods, int mods_size)
  {
    int call_id = *((int*)object);

    std::vector<ModioMod*> mods_vector;
    for(int i=0; i<mods_size; i++)
    {
      mods_vector.push_back(&(mods[i]));
    }

    get_mods_calls[call_id]->callback(get_mods_calls[call_id]->object, (const ModioResponse&)response, mods_vector);

    delete (int*)object;
    delete get_mods_calls[call_id];
    get_mods_calls.erase(call_id);
  }

  void onEditMod(void* object, ModioResponse response, ModioMod* mod)
  {
    int call_id = *((int*)object);

    ModioMod modio_mod;
    edit_mod_calls[call_id]->callback(edit_mod_calls[call_id]->object, (const ModioResponse&)response, modio_mod);

    delete (int*)object;
    delete edit_mod_calls[call_id];
    edit_mod_calls.erase(call_id);
  }

  void onDeleteMod(void* object, ModioResponse response, ModioMod* mod)
  {
    int call_id = *((int*)object);

    ModioMod modio_mod;
    delete_mod_calls[call_id]->callback(delete_mod_calls[call_id]->object, (const ModioResponse&)response, modio_mod);

    delete (int*)object;
    delete delete_mod_calls[call_id];
    delete_mod_calls.erase(call_id);
  }

  bool Instance::getMods(void* object, modio::Filter& filter, const std::function<void(void* object, const ModioResponse&, const std::vector<ModioMod*> & mods)>& callback)
  {
    const struct GetModsCall* get_mods_call = new GetModsCall{object, callback};
    get_mods_calls[this->current_call_id] = (GetModsCall*)get_mods_call;

    modioGetMods((void*)new int(this->current_call_id), filter.getFilter(), &onGetMods);

    this->current_call_id++;
    return true;
  }

  void Instance::editMod(void* object, u32 mod_id, modio::ModHandler& mod_handler, const std::function<void(void* object, const ModioResponse& response, const ModioMod& mod)>& callback)
  {
    const struct EditModCall* edit_mod_call = new EditModCall{object, callback};
    edit_mod_calls[this->current_call_id] = (EditModCall*)edit_mod_call;

    modioEditMod((void*)new int(this->current_call_id), mod_id, mod_handler.getModioModHandler(), &onEditMod);

    this->current_call_id++;
  }

  void Instance::deleteMod(void* object, u32 mod_id, const std::function<void(void* object, const ModioResponse& response, const ModioMod& mod)>& callback)
  {
    const struct DeleteModCall* delete_mod_call = new DeleteModCall{object, callback};
    delete_mod_calls[this->current_call_id] = (DeleteModCall*)delete_mod_call;

    modioDeleteMod((void*)new int(this->current_call_id), mod_id, &onDeleteMod);

    this->current_call_id++;
  }
}
