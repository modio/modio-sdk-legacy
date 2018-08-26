#include "c++/schemas/Comment.h"

namespace modio
{
	void Comment::initialize(ModioComment modio_comment)
	{
		this->id = modio_comment.id;
		this->mod_id = modio_comment.mod_id;
		this->date_added = modio_comment.date_added;
		this->reply_id = modio_comment.reply_id;
		this->karma = modio_comment.karma;
		this->karma_guest = modio_comment.karma_guest;
		if(modio_comment.thread_position)
			this->thread_position = modio_comment.thread_position;
		if(modio_comment.content)
			this->content = modio_comment.content;
		this->user.initialize(modio_comment.user);
	}

	nlohmann::json Comment::toJson()
	{
		nlohmann::json comment_json;

		comment_json["id"] = this->id;
		comment_json["mod_id"] = this->mod_id;
		comment_json["date_added"] = this->date_added;
		comment_json["reply_id"] = this->reply_id;
		comment_json["karma"] = this->karma;
		comment_json["karma_guest"] = this->karma_guest;
		comment_json["thread_position"] = this->thread_position;
		comment_json["content"] = this->content;
		comment_json["user"] = this->user.toJson();

		return comment_json;
	}
}
