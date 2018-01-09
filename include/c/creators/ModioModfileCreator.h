#ifndef MODIO_MODIO_MODFILE_CREATOR_H
#define MODIO_MODIO_MODFILE_CREATOR_H

#include "Globals.h"
#include "c/ModioC.h"

namespace modio
{
  std::multimap<std::string, std::string> convertModfileCreatorToMultimap(ModioModfileCreator* modfile_creator);
}

#endif
