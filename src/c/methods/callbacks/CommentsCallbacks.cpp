#include "c/methods/callbacks/CommentsCallbacks.h"

std::map<u32, GetAllModCommentsParams *> get_all_mod_comments_callbacks;
std::map<u32, GetModCommentParams *> get_mod_comment_callbacks;
std::map<u32, DeleteModCommentParams *> delete_mod_comment_callbacks;

void modioOnGetAllModComments(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;
  ModioComment *comments_array = NULL;
  u32 comments_array_size = 0;

  if (response.code == 200)
  {
    if (modio::hasKey(response_json, "data"))
    {
      comments_array_size = (u32)response_json["data"].size();
      comments_array = new ModioComment[comments_array_size];
      for (u32 i = 0; i < comments_array_size; i++)
      {
        modioInitComment(&(comments_array[i]), response_json["data"][i]);
      }
    }
    else
    {
      modio::writeLogLine("Could not retreive data array from API.", MODIO_DEBUGLEVEL_ERROR);
      response.code = 0;
    }
  }

  get_all_mod_comments_callbacks[call_number]->callback(get_all_mod_comments_callbacks[call_number]->object, response, comments_array, comments_array_size);

  delete get_all_mod_comments_callbacks[call_number];
  get_all_mod_comments_callbacks.erase(call_number);

  modioFreeResponse(&response);
  for (u32 i = 0; i < comments_array_size; i++)
    modioFreeComment(&(comments_array[i]));
  if (comments_array)
    delete[] comments_array;
}

void modioOnGetModComment(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioComment comment;
  modioInitComment(&comment, response_json);

  get_mod_comment_callbacks[call_number]->callback(get_mod_comment_callbacks[call_number]->object, response, comment);

  delete get_mod_comment_callbacks[call_number];
  get_mod_comment_callbacks.erase(call_number);

  modioFreeResponse(&response);
  modioFreeComment(&comment);
}

void modioOnDeleteModComment(u32 call_number, u32 response_code, nlohmann::json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  delete_mod_comment_callbacks[call_number]->callback(delete_mod_comment_callbacks[call_number]->object, response);

  delete delete_mod_comment_callbacks[call_number];
  delete_mod_comment_callbacks.erase(call_number);

  modioFreeResponse(&response);
}

void clearCommentsCallbackParams()
{
  for (auto get_all_mod_comments_callback : get_all_mod_comments_callbacks)
    delete get_all_mod_comments_callback.second;
  get_all_mod_comments_callbacks.clear();

  for (auto get_mod_comment_callback : get_mod_comment_callbacks)
    delete get_mod_comment_callback.second;
  get_mod_comment_callbacks.clear();

  for (auto delete_mod_comment_callback : delete_mod_comment_callbacks)
    delete delete_mod_comment_callback.second;
  delete_mod_comment_callbacks.clear();
}