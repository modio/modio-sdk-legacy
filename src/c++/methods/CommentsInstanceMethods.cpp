#include "c++/ModIOInstance.h"

namespace modio
{
void Instance::getAllModComments(u32 mod_id, modio::FilterCreator &filter, const std::function<void(const modio::Response &response, const std::vector<modio::Comment> &comments)> &callback)
{
    const struct GetAllModCommentsCall *get_all_mod_comments_call = new GetAllModCommentsCall{callback};
    get_all_mod_comments_calls[this->current_call_id] = (GetAllModCommentsCall *)get_all_mod_comments_call;

    modioGetAllModComments((void *)new u32(this->current_call_id), mod_id, *filter.getFilter(), &onGetAllModComments);

    this->current_call_id++;
}

void Instance::getModComment(u32 mod_id, u32 comment_id, const std::function<void(const modio::Response &response, const modio::Comment &comment)> &callback)
{
    const struct GetModCommentCall *get_mod_comment_call = new GetModCommentCall{callback};
    get_mod_comment_calls[this->current_call_id] = (GetModCommentCall *)get_mod_comment_call;

    modioGetModComment((void *)new u32(this->current_call_id), mod_id, comment_id, &onGetModComment);

    this->current_call_id++;
}

void Instance::deleteModComment(u32 mod_id, u32 comment_id, const std::function<void(const modio::Response &response)> &callback)
{
    const struct DeleteModCommentCall *delete_mod_comment_call = new DeleteModCommentCall{callback};
    delete_mod_comment_calls[this->current_call_id] = (DeleteModCommentCall *)delete_mod_comment_call;

    modioDeleteModComment((void *)new u32(this->current_call_id), mod_id, comment_id, &onDeleteModComment);

    this->current_call_id++;
}
} // namespace modio
