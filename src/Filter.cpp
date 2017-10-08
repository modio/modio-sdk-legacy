#include "Filter.h"

namespace modio
{
  string getFilterString(Filter* filter)
  {
    string filter_string = "";
    for(map<string, string>::iterator i = filter->params.begin();
          i != filter->params.end();
          i++)
    {
      if(filter_string!="")
        filter_string += "&";
      filter_string += (*i).first + "=" + (*i).second;
    }
    return filter_string;
  }

  void setFilterSort(Filter* filter, string field, bool ascending)
  {
    filter->params["_sort"] = field;
  }

  void setFilterLimit(Filter* filter, int limit)
  {
    filter->params["_limit"] = toString(limit);
  }

  void setFilterOffset(Filter* filter, int offset)
  {
    filter->params["_offset"] = toString(offset);
  }

  void setFilterCursor(Filter* filter, int cursor)
  {
    filter->params["_cursor"] = toString(cursor);
  }

  void setFilterFullTextSearch(Filter* filter, string text)
  {
    filter->params["_q"] = text;
  }

  void addFilterLikeField(Filter* filter, string field, string value)
  {
    filter->params[field + "-lk"] = value;
  }

  void addFilterNotLikeField(Filter* filter, string field, string value)
  {
    filter->params[field + "-not-lk"] = value;
  }

  void addFilterInField(Filter* filter, string field, string value)
  {
    string key = field + "-in";

    if(filter->params.find(key) == filter->params.end())
    {
      filter->params[key] = value;
    }else
    {
      filter->params[key] += string(",") + value;
    }
  }

  void addFilterNotInField(Filter* filter, string field, string value)
  {
    string key = field + "-not-in";

    if(filter->params.find(key) == filter->params.end())
    {
      filter->params[key] = value;
    }else
    {
      filter->params[key] += string(",") + value;
    }
  }

  void addFilterMinField(Filter* filter, string field, double value)
  {
    filter->params[field + "-min"] = toString(value);
  }

  void addFilterMaxField(Filter* filter, string field, double value)
  {
    filter->params[field + "-max"] = toString(value);
  }

  void addFilterSmallerThanField(Filter* filter, string field, double value)
  {
    filter->params[field + "-st"] = toString(value);
  }

  void addFilterGreaterThanField(Filter* filter, string field, double value)
  {
    filter->params[field + "-gt"] = toString(value);
  }

  void addFilterNotEqualField(Filter* filter, string field, string value)
  {
    filter->params[field + "-not"] = value;
  }
}
