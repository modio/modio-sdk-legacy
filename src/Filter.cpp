#include "Filter.h"

extern "C"
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

  string getFilterString(Filter* filter)
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

  void initFilter(Filter* filter)
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

  void setFilterSort(Filter* filter, char* field, bool ascending)
  {
    string sort_str = string("_sort=") + field;
    filter->sort = (char*)sort_str.c_str();
  }

  void setFilterLimit(Filter* filter, int limit)
  {
    string limit_str = string("_limit=") + modio::toString(limit);
    filter->limit = (char*)limit_str.c_str();
  }

  void setFilterOffset(Filter* filter, int offset)
  {
    string offset_str = string("_offset=") + modio::toString(offset);
    filter->offset = (char*)offset_str.c_str();
  }

  void setFilterCursor(Filter* filter, int cursor)
  {
    string cursor_str = string("_cursor=") + modio::toString(cursor);
    filter->cursor = (char*)cursor_str.c_str();
  }

  void setFilterFullTextSearch(Filter* filter, char* text)
  {
    string full_text_search_str = string("_q=") + text;
    filter->full_text_search = (char*)full_text_search_str.c_str();
  }

  void addFilterLikeField(Filter* filter, char* field, char* value)
  {
    string like_str = string(field) + "-lk=" + value;
    filter->like = (char*)like_str.c_str();
  }

  void addFilterNotLikeField(Filter* filter, char* field, char* value)
  {
    string not_like_str = string(field) + "-not-lk=" + value;
    filter->not_like = (char*)not_like_str.c_str();
  }

  void addFilterInField(Filter* filter, char* field, char* value)
  {
    if(strcmp(filter->in,"")==0)
    {
      string in_str = string(field) + "-in=" + value;
      filter->in = (char*)in_str.c_str();
    }else
    {
      string in_str = filter->in + string(",") + value;
      filter->in = (char*)in_str.c_str();
    }
  }

  void addFilterNotInField(Filter* filter, char* field, char* value)
  {
    if(strcmp(filter->not_in,"")==0)
    {
      string not_in_str = string(field) + "-not-in=" + value;
      filter->not_in = (char*)not_in_str.c_str();
    }else
    {
      string not_in_str = filter->not_in + string(",") + value;
      filter->not_in = (char*)not_in_str.c_str();
    }
  }

  void addFilterMinField(Filter* filter, char* field, double value)
  {
    string min_str = string(field) + "-min=" + modio::toString(value);
    filter->min = (char*)min_str.c_str();
  }

  void addFilterMaxField(Filter* filter, char* field, double value)
  {
    string max_str = string(field) + "-max=" + modio::toString(value);
    filter->max = (char*)max_str.c_str();
  }

  void addFilterSmallerThanField(Filter* filter, char* field, double value)
  {
    string smaller_than_str = string(field) + "-st=" + modio::toString(value);
    filter->smaller_than = (char*)smaller_than_str.c_str();
  }

  void addFilterGreaterThanField(Filter* filter, char* field, double value)
  {
    string greater_than_str = string(field) + "-gt=" + modio::toString(value);
    filter->greater_than = (char*)greater_than_str.c_str();
  }

  void addFilterNotEqualField(Filter* filter, char* field, char* value)
  {
    string not_equal_str = string(field) + "-not=" + value;
    filter->not_equal = (char*)not_equal_str.c_str();
  }
}
