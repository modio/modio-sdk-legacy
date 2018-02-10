#include "c++/ModIOInstance.h"

namespace modio
{
  void Instance::getAuthenticatedUser(const std::function<void(const modio::Response& response, const modio::User& user)>& callback)
  {
    const struct GetAuthenticatedUserCall* get_authenticated_user_call = new GetAuthenticatedUserCall{callback};
    get_authenticated_user_calls[this->current_call_id] = (GetAuthenticatedUserCall*)get_authenticated_user_call;

    modioGetAuthenticatedUser((void*)new u32(this->current_call_id), &onGetAuthenticatedUser);

    this->current_call_id++;
  }
}
