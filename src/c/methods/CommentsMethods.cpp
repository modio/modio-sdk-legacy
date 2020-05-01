#include <map>                      // for map
#include <string>                   // for operator+
#include "ModUtility.h"             // for getCallFileFr...
#include "wrappers/CurlWrapper.h"   // for getCallNumber
#include "Globals.h"                // for GAME_ID, MODI...
#include "Utility.h"                // for toString, get...
#include "c/ModioC.h"               // for u32, ModioRes...
#include "c/creators/ModioFilterCreator.h"   // for getFilterString
#include "ModioUtility.h"           // for GenericReques...
#include "c/methods/callbacks/CommentsCallbacks.h"      // for GetAllModComm...
#include "dependencies/nlohmann/json.hpp"               // for json

extern "C"
{
  void modioGetAllModCommentsFilterString(void *object, u32 mod_id, char const *filter_string, u32 cache_max_age_seconds, void (*callback)(void *object, ModioResponse response, ModioComment comments[], u32 comments_size))
  {
    std::string url_without_api_key = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/comments?" + (filter_string ? filter_string : "");
    std::string url = url_without_api_key + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_all_mod_comments_callbacks[call_number] = new GetAllModCommentsParams;
    get_all_mod_comments_callbacks[call_number]->callback = callback;
    get_all_mod_comments_callbacks[call_number]->object = object;
    get_all_mod_comments_callbacks[call_number]->url = url_without_api_key;
    get_all_mod_comments_callbacks[call_number]->is_cache = false;

    std::string cache_filename = modio::getCallFileFromCache(url_without_api_key, cache_max_age_seconds);
    if (cache_filename != "")
    {
        nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache/" + cache_filename);
        if (!cache_file_json.empty())
        {
            get_all_mod_comments_callbacks[call_number]->is_cache = true;
            modioOnGetAllModComments(call_number, 200, cache_file_json);
            return;
        }
    }
    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetAllModComments);
  }

  void modioGetAllModComments(void *object, u32 mod_id, ModioFilterCreator filter, void (*callback)(void *object, ModioResponse response, ModioComment comments[], u32 comments_size))
  {
    std::string filter_string = modio::getFilterString(&filter);
    modioGetAllModCommentsFilterString(object, mod_id, filter_string.c_str(), filter.cache_max_age_seconds, callback);
  }

  void modioGetModComment(void *object, u32 mod_id, u32 comment_id, void (*callback)(void *object, ModioResponse response, ModioComment comment))
  {
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/comments/" + modio::toString(comment_id) + "?api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_mod_comment_callbacks[call_number] = new GetModCommentParams;
    get_mod_comment_callbacks[call_number]->callback = callback;
    get_mod_comment_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetModComment);
  }

  void modioDeleteModComment(void *object, u32 mod_id, u32 comment_id, void (*callback)(void *object, ModioResponse response))
  {
		if(!modioIsLoggedIn())
		{
			modio::processGenericLocalUnauthorizedRequest(object, callback);
			return;
		}
    
    std::map<std::string, std::string> data;
    u32 call_number = modio::curlwrapper::getCallNumber();

    delete_mod_comment_callbacks[call_number] = new GenericRequestParams;
    delete_mod_comment_callbacks[call_number]->callback = callback;
    delete_mod_comment_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/comments/" + modio::toString(comment_id);

    modio::curlwrapper::deleteCall(call_number, url, modio::getUrlEncodedHeaders(), data, &modioOnDeleteModComment);
  }
}
