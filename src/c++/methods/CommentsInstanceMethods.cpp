#include "c++/ModIOInstance.h"
#include "ModioUtility.h"
#include "c++/methods/callbacks/CommentsInstanceCallbacks.h"
#include "c++/creators/FilterCreator.h"

namespace modio
{
void Instance::getAllModComments(u32 mod_id, modio::FilterCreator &filter, const std::function<void(const modio::Response &response, const std::vector<modio::Comment> &comments)> &callback)
{
    struct GetAllModCommentsCall *get_all_mod_comments_call = new GetAllModCommentsCall{callback};
    get_all_mod_comments_calls[current_call_id] = get_all_mod_comments_call;

    modioGetAllModComments((void*)((uintptr_t)current_call_id), mod_id, *filter.getFilter(), &onGetAllModComments);

    current_call_id++;
}

void Instance::getModComment(u32 mod_id, u32 comment_id, const std::function<void(const modio::Response &response, const modio::Comment &comment)> &callback)
{
    struct GetModCommentCall *get_mod_comment_call = new GetModCommentCall{callback};
    get_mod_comment_calls[current_call_id] = get_mod_comment_call;

    modioGetModComment((void*)((uintptr_t)current_call_id), mod_id, comment_id, &onGetModComment);

    current_call_id++;
}

void Instance::deleteModComment(u32 mod_id, u32 comment_id, const std::function<void(const modio::Response &response)> &callback)
{
    struct GenericCall *delete_mod_comment_call = new GenericCall{callback};
    delete_mod_comment_calls[current_call_id] = delete_mod_comment_call;

    modioDeleteModComment((void*)((uintptr_t)current_call_id), mod_id, comment_id, &onDeleteModComment);

    current_call_id++;
}
} // namespace modio
