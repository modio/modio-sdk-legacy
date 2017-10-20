#include "data_containers/Cursor.h"

extern "C"
{
  void modioInitCursor(ModioCursor* cursor, json cursor_json)
  {
    cursor->current = -1;
    if(modio::hasKey(cursor_json, "current"))
      cursor->current = cursor_json["current"];

    cursor->prev = -1;
    if(modio::hasKey(cursor_json, "prev"))
      cursor->prev = cursor_json["prev"];

    cursor->next = -1;
    if(modio::hasKey(cursor_json, "next"))
      cursor->next = cursor_json["next"];

    cursor->count = -1;
    if(modio::hasKey(cursor_json, "count"))
      cursor->count = cursor_json["count"];
  }

  void modioFreeCursor(ModioCursor* cursor)
  {
    delete cursor;
  }
}
