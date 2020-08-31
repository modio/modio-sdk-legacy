#ifndef MODIO_PLATFORM_H
#define MODIO_PLATFORM_H

#include "Utility.h"

namespace modio
{
#if defined(MODIO_WINDOWS_DETECTED)
  namespace windows_platform{};
  namespace platform = windows_platform;
#elif defined(MODIO_OSX_DETECTED) || defined(MODIO_LINUX_DETECTED)
  namespace unix_platform{};
  namespace platform = unix_platform;
#else
#error UNKNOWN PLATFORM
#endif
}

#endif
    
