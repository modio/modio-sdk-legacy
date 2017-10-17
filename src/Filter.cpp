#include "Filter.h"

extern "C"
{
  void modioInitFilter(ModioFilter* filter)
  {
    filter->sort = NULL;
    filter->limit = NULL;
    filter->offset = NULL;
    filter->cursor = NULL;
    filter->full_text_search = NULL;
    filter->like = NULL;
    filter->not_like = NULL;
    filter->in = NULL;
    filter->not_in = NULL;
    filter->min = NULL;
    filter->max = NULL;
    filter->smaller_than = NULL;
    filter->greater_than = NULL;
    filter->not_equal = NULL;
  }

  void modioSetFilterSort(ModioFilter* filter, char* field, bool ascending)
  {
    if(filter->sort)
      delete filter->sort;
    string ascending_str = "";
    if(!ascending)
      ascending_str = "-";
    string sort_str = string("_sort=") + ascending_str + field;
    filter->sort = new char[sort_str.size() + 1];
    strcpy(filter->sort, sort_str.c_str());
  }

  void modioSetFilterLimit(ModioFilter* filter, int limit)
  {
    if(filter->limit)
      delete filter->limit;
    string limit_str = string("_limit=") + modio::toString(limit);
    filter->limit = new char[limit_str.size() + 1];
    strcpy(filter->limit, limit_str.c_str());
  }

  void modioSetFilterOffset(ModioFilter* filter, int offset)
  {
    if(filter->offset)
      delete filter->offset;
    string offset_str = string("_offset=") + modio::toString(offset);
    filter->offset = new char[offset_str.size() + 1];
    strcpy(filter->offset, offset_str.c_str());
  }

  void modioSetFilterCursor(ModioFilter* filter, int cursor)
  {
    if(filter->cursor)
      delete filter->cursor;
    string cursor_str = string("_cursor=") + modio::toString(cursor);
    filter->cursor = new char[cursor_str.size() + 1];
    strcpy(filter->cursor, cursor_str.c_str());
  }

  void modioSetFilterFullTextSearch(ModioFilter* filter, char* text)
  {
    if(filter->full_text_search)
      delete filter->full_text_search;
    string full_text_search_str = string("_q=") + text;
    filter->full_text_search = new char[full_text_search_str.size() + 1];
    strcpy(filter->full_text_search, full_text_search_str.c_str());
  }

  void modioAddFilterLikeField(ModioFilter* filter, char* field, char* value)
  {
    if(filter->like)
      delete filter->like;
    string like_str = string(field) + "-lk=" + value;
    filter->like = new char[like_str.size() + 1];
    strcpy(filter->like, like_str.c_str());
  }

  void modioAddFilterNotLikeField(ModioFilter* filter, char* field, char* value)
  {
    if(filter->not_like)
      delete filter->not_like;
    string not_like_str = string(field) + "-not-lk=" + value;
    filter->not_like = new char[not_like_str.size() + 1];
    strcpy(filter->not_like, not_like_str.c_str());
  }

  void modioAddFilterInField(ModioFilter* filter, char* field, char* value)
  {
    if(filter->in)
      delete filter->in;

    if(strcmp(filter->in,"")==0)
    {
      string in_str = string(field) + "-in=" + value;
      filter->in = new char[in_str.size() + 1];
      strcpy(filter->in, in_str.c_str());
    }else
    {
      string in_str = filter->in + string(",") + value;
      filter->in = new char[in_str.size() + 1];
      strcpy(filter->in, in_str.c_str());
    }
  }

  void modioAddFilterNotInField(ModioFilter* filter, char* field, char* value)
  {
    if(filter->not_in)
      delete filter->not_in;

    if(strcmp(filter->not_in,"")==0)
    {
      string not_in_str = string(field) + "-not-in=" + value;
      filter->not_in = new char[not_in_str.size() + 1];
      strcpy(filter->not_in, not_in_str.c_str());
    }else
    {
      string not_in_str = filter->not_in + string(",") + value;
      filter->not_in = new char[not_in_str.size() + 1];
      strcpy(filter->not_in, not_in_str.c_str());
    }
  }

  void modioAddFilterMinField(ModioFilter* filter, char* field, double value)
  {
    if(filter->min)
      delete filter->min;

    string min_str = string(field) + "-min=" + modio::toString(value);
    filter->min = new char[min_str.size() + 1];
    strcpy(filter->min, min_str.c_str());
  }

  void modioAddFilterMaxField(ModioFilter* filter, char* field, double value)
  {
    if(filter->max)
      delete filter->max;

    string max_str = string(field) + "-max=" + modio::toString(value);
    filter->max = new char[max_str.size() + 1];
    strcpy(filter->max, max_str.c_str());
  }

  void modioAddFilterSmallerThanField(ModioFilter* filter, char* field, double value)
  {
    if(filter->smaller_than)
      delete filter->smaller_than;

    string smaller_than_str = string(field) + "-st=" + modio::toString(value);
    filter->smaller_than = new char[smaller_than_str.size() + 1];
    strcpy(filter->smaller_than, smaller_than_str.c_str());
  }

  void modioAddFilterGreaterThanField(ModioFilter* filter, char* field, double value)
  {
    if(filter->greater_than)
      delete filter->greater_than;

    string greater_than_str = string(field) + "-gt=" + modio::toString(value);
    filter->greater_than = new char[greater_than_str.size() + 1];
    strcpy(filter->greater_than, greater_than_str.c_str());
  }

  void modioAddFilterNotEqualField(ModioFilter* filter, char* field, char* value)
  {
    if(filter->not_equal)
      delete filter->not_equal;

    string not_equal_str = string(field) + "-not=" + value;
    filter->not_equal = new char[not_equal_str.size() + 1];
    strcpy(filter->not_equal, not_equal_str.c_str());
  }
}

namespace modio
{
  string addParam(string filter_string, char* param)
  {
    if(param)
    {
      if(filter_string != "")
        filter_string += "&";
      filter_string += param;
    }
    return filter_string;
  }

  string getFilterString(ModioFilter* filter)
  {
    string filter_string = "";
    filter_string = addParam(filter_string, filter->sort);
    filter_string = addParam(filter_string, filter->limit);
    filter_string = addParam(filter_string, filter->offset);
    filter_string = addParam(filter_string, filter->cursor);
    filter_string = addParam(filter_string, filter->full_text_search);
    filter_string = addParam(filter_string, filter->like);
    filter_string = addParam(filter_string, filter->not_like);
    filter_string = addParam(filter_string, filter->in);
    filter_string = addParam(filter_string, filter->not_in);
    filter_string = addParam(filter_string, filter->min);
    filter_string = addParam(filter_string, filter->max);
    filter_string = addParam(filter_string, filter->smaller_than);
    filter_string = addParam(filter_string, filter->greater_than);
    filter_string = addParam(filter_string, filter->not_equal);
    return filter_string;
  }
}
