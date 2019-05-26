#include "c/methods/ModfileMethods.h"

extern "C"
{
  void modioGetModfile(void* object, u32 mod_id, u32 modfile_id, void (*callback)(void* object, ModioResponse response, ModioModfile modfile))
  {
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/files/" + modio::toString(modfile_id) + "?api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_modfile_callbacks[call_number] = new GetModfileParams;
    get_modfile_callbacks[call_number]->callback = callback;
    get_modfile_callbacks[call_number]->object = object;

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetModfile);
  }

  void modioGetAllModfilesFilterString(void* object, u32 mod_id, char const* filter_string, u32 cache_max_age_seconds, void (*callback)(void* object, ModioResponse response, ModioModfile modfiles[], u32 modfiles_size))
  {
    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/files?" + (filter_string ? filter_string : "") + "&api_key=" + modio::API_KEY;

    u32 call_number = modio::curlwrapper::getCallNumber();

    get_all_modfiles_callbacks[call_number] = new GetAllModfilesParams;
    get_all_modfiles_callbacks[call_number]->callback = callback;
    get_all_modfiles_callbacks[call_number]->object = object;
    get_all_modfiles_callbacks[call_number]->url = url;
    get_all_modfiles_callbacks[call_number]->is_cache = false;

    std::string cache_filename = modio::getCallFileFromCache(url, cache_max_age_seconds);
    if(cache_filename != "")
    {
      nlohmann::json cache_file_json = modio::openJson(modio::getModIODirectory() + "cache/" + cache_filename);

      if(!cache_file_json.empty())
      {
        get_all_modfiles_callbacks[call_number]->is_cache = true;
        modioOnGetAllModfiles(call_number, 200, cache_file_json);
        return;
      }
    }

    modio::curlwrapper::get(call_number, url, modio::getHeaders(), &modioOnGetAllModfiles);
  }

  void modioGetAllModfiles(void* object, u32 mod_id, ModioFilterCreator filter, void (*callback)(void* object, ModioResponse response, ModioModfile modfiles[], u32 modfiles_size))
  {
    std::string filter_string = modio::getFilterString(&filter);
    modioGetAllModfilesFilterString(object, mod_id, filter_string.c_str(), filter.cache_max_age_seconds, callback);
  }

  void modioAddModfile(u32 mod_id, ModioModfileCreator modfile_creator)
  {
    modio::curlwrapper::queueModfileUpload(mod_id, &modfile_creator);
  }

  void modioEditModfile(void* object, u32 mod_id, u32 modfile_id, ModioModfileEditor modfile_editor, void (*callback)(void* object, ModioResponse response, ModioModfile modfile))
  {
    u32 call_number = modio::curlwrapper::getCallNumber();

    edit_modfile_callbacks[call_number] = new EditModfileParams;
    edit_modfile_callbacks[call_number]->modfile_id = modfile_id;
    edit_modfile_callbacks[call_number]->callback = callback;
    edit_modfile_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/files/" + modio::toString(modfile_id);

    std::multimap<std::string,std::string> modfile_params = modio::convertModfileEditorToMultimap(&modfile_editor);
    for(std::multimap<std::string,std::string>::iterator i = modfile_params.begin(); i != modfile_params.end(); i++)
    {
      if(i==modfile_params.begin())
        url+="?";
      else
        url+="&";
      url+=(*i).first + "=" + (*i).second;
    }

    modio::curlwrapper::put(call_number, url, modio::getHeaders(), modio::convertModfileEditorToMultimap(&modfile_editor), &modioOnModfileEdited);
  }

  void MODIO_DLL modioDeleteModfile(void* object, u32 mod_id, u32 modfile_id, void (*callback)(void* object, ModioResponse response))
  {
    u32 call_number = modio::curlwrapper::getCallNumber();

    delete_modfile_callbacks[call_number] = new GenericRequestParams;
    delete_modfile_callbacks[call_number]->callback = callback;
    delete_modfile_callbacks[call_number]->object = object;

    std::string url = modio::MODIO_URL + modio::MODIO_VERSION_PATH + "games/" + modio::toString(modio::GAME_ID) + "/mods/" + modio::toString(mod_id) + "/files/" + modio::toString(modfile_id);
    
    std::map<std::string, std::string> data;

    modio::curlwrapper::deleteCall(call_number, url, modio::getHeaders(), data, &modioOnModfileDeleted);
  }
}
