#ifndef MODIO_MODIO_MOD_UPDATER_H
#define MODIO_MODIO_MOD_UPDATER_H

#include "Globals.h"
#include "Utility.h"
#include "extern_c/ModioC.h"

namespace modio
{
  std::multimap<std::string, std::string> getModfileUpdaterCurlFormCopyContentsParams(ModioModUpdater* mod_updater);
}

#endif
