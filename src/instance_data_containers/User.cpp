#include "instance_data_containers/User.h"

namespace modio
{
  void User::initialize(ModioUser modio_user)
  {
    this->id = modio_user.id;
    this->date_online = modio_user.date_online;
    this->username = modio_user.username;
    this->name_id = modio_user.name_id;
    this->timezone = modio_user.timezone;
    this->language = modio_user.language;
    this->profile_url = modio_user.profile_url;
    this->avatar.initialize(modio_user.avatar);
  }
}
