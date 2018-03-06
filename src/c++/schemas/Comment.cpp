#include "c++/schemas/Comment.h"

namespace modio
{
	void Comment::initialize(ModioComment modio_comment)
	{
		this->mod_id = modio_comment.mod_id;
		this->date_added = modio_comment.date_added;
	}

	json Comment::toJson()
	{
		json comment_json;

		comment_json["mod_id"] = this->mod_id;
		comment_json["date_added"] = this->date_added;

		return comment_json;
	}
}
