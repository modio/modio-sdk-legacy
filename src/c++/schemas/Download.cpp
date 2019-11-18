#include "c++/schemas/Download.h"
#include "c/ModioC.h"                      // for ModioDownload
#include "dependencies/nlohmann/json.hpp"  // for json

namespace modio
{
void Download::initialize(ModioDownload modio_download)
{
  date_expires = modio_download.date_expires;
  if (modio_download.binary_url)
    binary_url = modio_download.binary_url;
}

nlohmann::json toJson(Download &download)
{
  nlohmann::json download_json;

  download_json["date_expires"] = download.date_expires;
  download_json["binary_url"] = download.binary_url;

  return download_json;
}
} // namespace modio
