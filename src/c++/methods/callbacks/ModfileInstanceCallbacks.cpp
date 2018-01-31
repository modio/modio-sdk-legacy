#include "c++/ModIOInstance.h"

namespace modio
{
  std::map<u32, AddModfileCall*> add_modfile_calls;
  std::map<u32, EditModfileCall*> edit_modfile_calls;

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
