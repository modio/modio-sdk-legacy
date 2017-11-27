#ifndef MODIO_ERROR_H
#define MODIO_ERROR_H

#include "data_containers/ModioError.h"
#include "Globals.h"

namespace modio
{
  class Error
  {
  public:
    u32 code;
    std::string message;
    std::vector<std::string> errors;

    void initialize(ModioError error);
  };
}

#endif
