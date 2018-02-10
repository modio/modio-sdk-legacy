#include "c/methods/MeMethods.h"

extern "C"
{
  void modioGetAuthenticatedUser(void* object, void (*callback)(void* object, ModioResponse response, ModioUser user))
  {
    std::vector<std::string> headers;
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "me/?api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallCount();
    modio::curlwrapper::advanceCallCount();

    get_authenticated_user_callbacks[call_number] = new GetAuthenticatedUserParams;
    get_authenticated_user_callbacks[call_number]->callback = callback;
    get_authenticated_user_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, headers, &modioOnGetAuthenticatedUser);
  }
}
