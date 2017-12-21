#ifndef MODIO_MODFILE_HANDLER_H
#define MODIO_MODFILE_HANDLER_H

#include "Globals.h"
#include "extern_c/ModioC.h"

namespace modio
{
  std::multimap<std::string, std::string> modfileHandlerToMultimap(ModioModfileHandler* modfile_handler);
}

#endif
