#ifndef MODIO_ERROR_H
#define MODIO_ERROR_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using json = nlohmann::json;

extern "C"
{
  struct ModioError
  {
    int code;
    char* message;
    char** errors_array;
    int errors_array_size;
  };

  void modioInitError(ModioError* response, json image_json);
  void modioFreeError(ModioError* response);
}

#endif
