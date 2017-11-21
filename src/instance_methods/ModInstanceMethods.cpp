#include "ModIOInstance.h"

namespace modio
{
  struct GetModsCall
  {
    void* object;
    const std::function<void(void* object, const ModioResponse&, std::vector<ModioMod*> mods)> callback;
  };

  std::map<int, GetModsCall*> get_mods_calls;

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

  bool Instance::getMods(void* object, modio::Filter& filter, const std::function<void(void* object, const ModioResponse&, const std::vector<ModioMod*> & mods)>& callback)
  {
    const struct GetModsCall* get_mods_call = new GetModsCall{object, callback};
    get_mods_calls[this->current_call_id] = (GetModsCall*)get_mods_call;

    modioGetMods((void*)new int(this->current_call_id), filter.getFilter(), &onGetMods);

    this->current_call_id++;
    return true;
  }
}
