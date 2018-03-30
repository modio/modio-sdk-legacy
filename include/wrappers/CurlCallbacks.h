#ifndef MODIO_CURL_CALLBACKS_H
#define MODIO_CURL_CALLBACKS_H

#include "wrappers/CurlUtility.h"
#include "wrappers/CurlWrapper.h"
#include "wrappers/CurlProgressFunctions.h"
#include "wrappers/CurlWriteFunctions.h"

namespace modio
{
namespace curlwrapper
{

void onJsonRequestFinished(CURL* curl);
void onDownloadFinished(CURL* curl);
void onModDownloadFinished(CURL* curl);

}
}

#endif