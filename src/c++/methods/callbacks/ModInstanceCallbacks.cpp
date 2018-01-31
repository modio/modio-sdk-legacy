#include "c++/ModIOInstance.h"

namespace modio
{
  std::map<u32, GetModCall*> get_mod_calls;
  std::map<u32, GetModsCall*> get_mods_calls;
  std::map<u32, AddModCall*> add_mod_calls;
  std::map<u32, EditModCall*> edit_mod_calls;
  std::map<u32, DeleteModCall*> delete_mod_calls;
  std::map<u32, InstallModCall*> install_mod_calls;

  void onGetMod(void* object, ModioResponse modio_response, ModioMod mod)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    modio::Mod modio_mod;

    if(modio_response.code == 200)
    {
      modio_mod.initialize(mod);
    }

    get_mod_calls[call_id]->callback((const Response&)response, modio_mod);

    delete (u32*)object;
    delete get_mod_calls[call_id];
    get_mod_calls.erase(call_id);
  }

  void onGetMods(void* object, ModioResponse modio_response, ModioMod mods[], u32 mods_size)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    std::vector<modio::Mod> mods_vector;
    mods_vector.resize(mods_size);
    for(u32 i=0; i < mods_size; i++)
    {
      mods_vector[i].initialize(mods[i]);
    }

    get_mods_calls[call_id]->callback((const Response&)response, mods_vector);

    delete (u32*)object;
    delete get_mods_calls[call_id];
    get_mods_calls.erase(call_id);
  }

  void onAddMod(void* object, ModioResponse modio_response, ModioMod mod)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    modio::Mod modio_mod;

    if(modio_response.code == 201)
    {
      modio_mod.initialize(mod);
    }

    add_mod_calls[call_id]->callback((const Response&)response, modio_mod);

    delete (u32*)object;
    delete add_mod_calls[call_id];
    add_mod_calls.erase(call_id);
  }

  void onEditMod(void* object, ModioResponse modio_response, ModioMod mod)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    modio::Mod modio_mod;
    edit_mod_calls[call_id]->callback((const Response&)response, modio_mod);

    delete (u32*)object;
    delete edit_mod_calls[call_id];
    edit_mod_calls.erase(call_id);
  }

  void onDeleteMod(void* object, ModioResponse modio_response, u32 mod_id)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    delete_mod_calls[call_id]->callback((const modio::Response&)response, mod_id);

    delete (u32*)object;
    delete delete_mod_calls[call_id];
    delete_mod_calls.erase(call_id);
  }

  void onInstallModfile(void* object, ModioResponse modio_response)
  {
    u32 call_id = *((u32*)object);
    modio::Response response;
    response.initialize(modio_response);
    install_mod_calls[call_id]->callback(response);
    delete (u32*)object;
    delete install_mod_calls[call_id];
    install_mod_calls.erase(call_id);
  }
}
