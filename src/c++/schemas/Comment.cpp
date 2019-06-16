#include "c++/schemas/Comment.h"

namespace modio
{
void Comment::initialize(ModioComment modio_comment)
{
	id = modio_comment.id;
	mod_id = modio_comment.mod_id;
	date_added = modio_comment.date_added;
	reply_id = modio_comment.reply_id;
	karma = modio_comment.karma;
	karma_guest = modio_comment.karma_guest;
	if (modio_comment.thread_position)
		thread_position = modio_comment.thread_position;
	if (modio_comment.content)
		content = modio_comment.content;
	user.initialize(modio_comment.user);
}

nlohmann::json toJson(Comment &comment)
{
	nlohmann::json comment_json;

	comment_json["id"] = comment.id;
	comment_json["mod_id"] = comment.mod_id;
	comment_json["date_added"] = comment.date_added;
	comment_json["reply_id"] = comment.reply_id;
	comment_json["karma"] = comment.karma;
	comment_json["karma_guest"] = comment.karma_guest;
	comment_json["thread_position"] = comment.thread_position;
	comment_json["content"] = comment.content;
	comment_json["user"] = modio::toJson(comment.user);

	return comment_json;
}
} // namespace modio
