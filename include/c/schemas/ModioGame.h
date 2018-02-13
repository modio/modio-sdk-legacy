#ifndef MODIO_MODIOGAME_H
#define MODIO_MODIOGAME_H

#include "dependencies/json/json.hpp"
#include "Utility.h"
#include "c/ModioC.h"
#include "c/schemas/ModioUser.h"
#include "c/schemas/ModioIcon.h"
#include "c/schemas/ModioLogo.h"
#include "c/schemas/ModioHeader.h"
#include "c/schemas/ModioGameTagOption.h"

using json = nlohmann::json;

extern "C"
{
  void modioInitGame(ModioGame* game, json game_json);
  void modioFreeGame(ModioGame* game);
}

#endif
