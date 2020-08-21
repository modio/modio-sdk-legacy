#include "c++/ModIOInstance.h"
#include "c++/methods/callbacks/GameInstanceCallbacks.h"

namespace modio
{
  void Instance::getGame(u32 game_id, const std::function<void(const modio::Response &, const modio::Game & game)>& callback)
  {
    struct GetGameCall* get_game_call = new GetGameCall{ callback };
    get_game_calls[current_call_id] = get_game_call;

    modioGetGame((void*)((uintptr_t)current_call_id), game_id, &onGetGame);

    current_call_id++;
  }
}