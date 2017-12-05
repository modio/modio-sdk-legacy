#ifndef MODIO_MODIOERROR_H
#define MODIO_MODIOERROR_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using json = nlohmann::json;

extern "C"
{
  struct ModioError
  {
    u32 code;
    char* message;
    char** errors_array;
    u32 errors_array_size;
  };

  void modioInitError(ModioError* error, json image_json);
  void modioFreeError(ModioError* error);
}

#endif
