#include "c++/ModIOInstance.h"

namespace modio
{
  std::map<u32, GetAuthenticatedUserCall*> get_authenticated_user_calls;

  void onGetAuthenticatedUser(void* object, ModioResponse modio_response, ModioUser modio_user)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    modio::User user;

    if(modio_response.code == 200)
    {
      user.initialize(modio_user);
    }

    get_authenticated_user_calls[call_id]->callback((const Response&)response, user);

    delete (u32*)object;
    delete get_authenticated_user_calls[call_id];
    get_authenticated_user_calls.erase(call_id);
  }
}
