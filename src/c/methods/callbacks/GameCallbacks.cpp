#include "c/methods/callbacks/GameCallbacks.h"

std::map< u32, GetGameParams* > get_game_callbacks;

void modioOnGetGame(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioGame game;
  modioInitGame(&game, response_json);

  get_game_callbacks[call_number]->callback(get_game_callbacks[call_number]->object, response, game);

  delete get_game_callbacks[call_number];
  get_game_callbacks.erase(call_number);

  modioFreeResponse(&response);
  modioFreeGame(&game);
}


void clearGameCallbackParams()
{
  for (auto get_game_callback : get_game_callbacks)
	delete get_game_callback.second;
  get_game_callbacks.clear();
}
