#include "c++/schemas/Download.h"

namespace modio
{
  void Download::initialize(ModioDownload modio_download)
  {
    this->date_expires = modio_download.date_expires;
    if(modio_download.binary_url)
      this->binary_url = modio_download.binary_url;
  }
}
