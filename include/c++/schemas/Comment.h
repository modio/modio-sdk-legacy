#ifndef MODIO_COMMENT_H
#define MODIO_COMMENT_H

#include "c/schemas/ModioComment.h"
#include "Globals.h"
#include "Utility.h"

namespace modio
{
	class Comment
	{
	public:
        u32 id;
        u32 mod_id;
        User submitted_by;
        u32 date_added;
        u32 reply_id;
        u32 karma;
        u32 karma_guest;
        std::string replay_position;
        std::string content;

		void initialize(ModioComment modio_comment);
		json toJson();
	};
}

#endif
