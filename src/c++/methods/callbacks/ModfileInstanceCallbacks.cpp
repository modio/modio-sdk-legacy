#include "c++/ModIOInstance.h"

namespace modio
{
  std::map<u32, GetModfileCall*> get_modfile_calls;
  std::map<u32, GetAllModfilesCall*> get_all_modfiles_calls;
  std::map<u32, AddModfileCall*> add_modfile_calls;
  std::map<u32, EditModfileCall*> edit_modfile_calls;

  void onGetModfile(void* object, ModioResponse modio_response, ModioModfile modfile)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    modio::Modfile modio_modfile;

    if(modio_response.code == 200)
    {
      modio_modfile.initialize(modfile);
    }

    get_modfile_calls[call_id]->callback((const Response&)response, modio_modfile);

    delete (u32*)object;
    delete get_modfile_calls[call_id];
    get_modfile_calls.erase(call_id);
  }

  void onGetAllModfiles(void* object, ModioResponse modio_response, ModioModfile modfiles[], u32 modfiles_size)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    std::vector<modio::Modfile> modfiles_vector;
    modfiles_vector.resize(modfiles_size);
    for(u32 i=0; i < modfiles_size; i++)
    {
      modfiles_vector[i].initialize(modfiles[i]);
    }

    get_all_modfiles_calls[call_id]->callback((const Response&)response, modfiles_vector);

    delete (u32*)object;
    delete get_all_modfiles_calls[call_id];
    get_all_modfiles_calls.erase(call_id);
  }

  void onAddModfile(void* object, ModioResponse modio_response, ModioModfile modio_modfile)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    modio::Modfile modfile;
    modfile.initialize(modio_modfile);

    add_modfile_calls[call_id]->callback(response, modfile);

    delete (u32*)object;
    delete add_modfile_calls[call_id];
    add_modfile_calls.erase(call_id);
  }

  void onEditModfile(void* object, ModioResponse modio_response, ModioModfile modio_modfile)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);
    modio::Modfile modfile;

    modfile.initialize(modio_modfile);
    edit_modfile_calls[call_id]->callback(response, modfile);
    delete (u32*)object;
    delete edit_modfile_calls[call_id];
    edit_modfile_calls.erase(call_id);
  }
}
