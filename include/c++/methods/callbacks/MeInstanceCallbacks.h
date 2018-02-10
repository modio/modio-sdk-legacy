namespace modio
{
  struct GetAuthenticatedUserCall
  {
    const std::function<void(const modio::Response&, const modio::User& user)> callback;
  };

  extern std::map<u32, GetAuthenticatedUserCall*> get_authenticated_user_calls;

  void onGetAuthenticatedUser(void* object, ModioResponse modio_response, ModioUser modio_user);
}
