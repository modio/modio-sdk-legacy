#ifndef MODIO_USER_H
#define MODIO_USER_H

#include "data_containers/ModioUser.h"
#include "Globals.h"
#include "instance_data_containers/Image.h"

namespace modio
{
  class User
  {
  public:
    u32 id;
    long date_online;
    std::string username;
    std::string name_id;
    std::string timezone;
    std::string language;
    std::string profile_url;
    modio::Image avatar;

    void initialize(ModioUser modio_user);
  };
}

#endif
