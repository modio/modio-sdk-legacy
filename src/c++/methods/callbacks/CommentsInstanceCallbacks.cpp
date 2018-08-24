#include "c++/ModIOInstance.h"

namespace modio
{
	std::map<u32, GetAllModCommentsCall*> get_all_mod_comments_calls;
	std::map<u32, GetModCommentCall*> get_mod_comment_calls;
	std::map<u32, DeleteModCommentCall*> delete_mod_comment_calls;

	void onGetAllModComments(void* object, ModioResponse modio_response, ModioComment* comments_array, u32 comments_array_size)
	{
		u32 call_id = *((u32*)object);

		modio::Response response;
		response.initialize(modio_response);

		std::vector<modio::Comment> comments_vector;
		comments_vector.resize(comments_array_size);
		for (u32 i = 0; i < comments_array_size; i++)
		{
			comments_vector[i].initialize(comments_array[i]);
		}

		get_all_mod_comments_calls[call_id]->callback((const Response&)response, comments_vector);

		delete (u32*)object;
		delete get_all_mod_comments_calls[call_id];
		get_all_mod_comments_calls.erase(call_id);
	}

	void onGetModComment(void* object, ModioResponse modio_response, ModioComment modio_comment)
  {
    u32 call_id = *((u32*)object);

    modio::Response response;
    response.initialize(modio_response);

    modio::Comment comment;

    if(modio_response.code == 200)
    {
      comment.initialize(modio_comment);
    }

    get_mod_comment_calls[call_id]->callback((const Response&)response, comment);

    delete (u32*)object;
    delete get_mod_comment_calls[call_id];
    get_mod_comment_calls.erase(call_id);
  }

	void onDeleteModComment(void* object, ModioResponse modio_response)
	{
		u32 call_id = *((u32*)object);

		modio::Response response;
		response.initialize(modio_response);

		delete_mod_comment_calls[call_id]->callback((const Response&)response);

		delete (u32*)object;
		delete delete_mod_comment_calls[call_id];
		delete_mod_comment_calls.erase(call_id);
	}
}
