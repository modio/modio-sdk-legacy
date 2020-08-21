#include "c/ModioC.h"
#include <string>                                       // for operator+
#include "Globals.h"       // for GAME_ID, MODI...
#include "Utility.h"        // for toString, get...
#include "wrappers/CurlWrapper.h"       // for getCallNumber
#include "c/methods/callbacks/GameCallbacks.h"       // for modioOnGetGame...

void modioGetGame(void* object, u32 game_id, void (*callback)(void* object, ModioResponse response, ModioGame game) )
{
  std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(game_id) + "?api_key=" + modio::API_KEY;

  u32 call_number = modio::curlwrapper::getCallNumber();

  get_game_callbacks[call_number] = new GetGameParams;
  get_game_callbacks[call_number]->callback = callback;
  get_game_callbacks[call_number]->object = object;

  modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetGame);
}