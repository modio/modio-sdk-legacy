#include "c++/methods/callbacks/GameInstanceCallbacks.h"
#include "c++/schemas/Response.h"

namespace modio
{
  std::map<u32, GetGameCall*> get_game_calls;

  void onGetGame(void* object, ModioResponse modio_response, ModioGame game)
  {
    u32 call_id = (u32)((uintptr_t)object);

    modio::Response response;
    response.initialize(modio_response);

    modio::Game modio_game;
    if (modio_response.code == 200)
    {
      modio_game.initialize(game);
    }

    get_game_calls[call_id]->callback(response, modio_game);

    delete get_game_calls[call_id];
    get_game_calls.erase(call_id);
  }

  void clearGameRequestCalls()
  {
    for (auto get_game_call : get_game_calls)
      delete get_game_call.second;
    get_game_calls.clear();
  }
} // namespace modio
