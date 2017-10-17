#ifndef MODIO_ERROR_H
#define MODIO_ERROR_H

#include "dependencies/json/json.hpp"
#include "Utility.h"

using namespace std;
using json = nlohmann::json;

extern "C"
{
  struct ModioError
  {
    int code;
    char* message;
    char* errors;
    int errors_size;
  };

  void modioInitError(ModioError* response, json image_json);
  void modioFreeError(ModioError* response);
}

#endif
