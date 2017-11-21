#include "ModIOSDK.h"

namespace modio
{
  class Instance
  {
  public:
    Instance(u32 id, const std::string& guid);

    bool isLoggedIn() const;
    void logout() const;
    bool emailRequest(void* object, const std::string& email, const std::function<void(void* object, const ModioResponse&, const std::string&)>& callback);
    bool emailExchange(void* object, const std::string& security_code, const std::function<void(void* object, const ModioResponse&)>& callback) const;
  };
}
