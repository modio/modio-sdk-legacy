#ifndef MODIO_FILESYSTEM_H
#define MODIO_FILESYSTEM_H

#include "Platform.h"
#include <fstream>

#if defined(MODIO_WINDOWS_DETECTED)
#include "WindowsFilesystem.h"
#elif defined(MODIO_OSX_DETECTED) || defined(MODIO_LINUX_DETECTED)
#include "UnixFilesystem.h"
#else
#error UNKNOWN PLATFORM
#endif

#endif
