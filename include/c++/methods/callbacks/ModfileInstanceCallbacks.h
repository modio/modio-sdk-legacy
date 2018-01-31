
namespace modio
{
  struct AddModfileCall
  {
    const std::function<void(const modio::Response& response, const modio::Modfile& modfile)> callback;
  };

  struct EditModfileCall
  {
    const std::function<void(const modio::Response& response, const modio::Modfile& modfile)> callback;
  };

  extern std::map<u32, AddModfileCall*> add_modfile_calls;
  extern std::map<u32, EditModfileCall*> edit_modfile_calls;

  void onAddModfile(void* object, ModioResponse modio_response, ModioModfile modio_modfile);
  void onEditModfile(void* object, ModioResponse modio_response, ModioModfile modio_modfile);
}
