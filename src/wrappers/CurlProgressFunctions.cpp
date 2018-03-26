#include "wrappers/CurlProgressFunctions.h"

namespace modio
{
namespace curlwrapper
{

i32 onModDownloadProgress(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
  QueuedModDownload *queued_mod_download = (QueuedModDownload *)clientp;
  queued_mod_download->current_progress = dlnow;
  queued_mod_download->total_size = dltotal;

  if(queued_mod_download->state == MODIO_MOD_PAUSING)
  {
    //curl_easy_pause(current_mod_download_curl_handle, CURLPAUSE_RECV);
    writeLogLine("Download paused at " + toString(dlnow), MODIO_DEBUGLEVEL_LOG);      
    updateModDownloadQueueFile();    
    return -1;
  }

  if(dltotal!=0)
    queued_mod_download->state = MODIO_MOD_DOWNLOADING;

  return 0;
}

}
}