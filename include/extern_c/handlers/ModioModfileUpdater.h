#ifndef MODIO_MODIO_MODFILE_UPDATER_H
#define MODIO_MODIO_MODFILE_UPDATER_H

#include "Globals.h"
#include "extern_c/ModioC.h"

namespace modio
{
  std::multimap<std::string, std::string> convertModfileUpdaterToMultimap(ModioModfileUpdater* modfile_updater);
}

#endif
