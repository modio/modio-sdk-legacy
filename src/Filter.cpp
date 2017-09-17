#include "Filter.h"

namespace modworks
{
  void addFilterField(FilterHandle* filter, string field)
  {
    if(filter->params.find("_fields") == filter->params.end())
    {
      filter->params["_fields"] = field;
    }else
    {
      filter->params["_fields"] += string(",") + field;
    }
  }

  void setFilterSort(FilterHandle* filter, string field, bool ascending)
  {
    filter->params["_sort"] = field;
  }

  void setFilterLimit(FilterHandle* filter, int limit)
  {
    filter->params["_limit"] = toString(limit);
  }

  void setFilterOffset(FilterHandle* filter, int offset)
  {
    filter->params["_offset"] = toString(offset);
  }

  void setFilterFullTextSearch(FilterHandle* filter, string text)
  {
    filter->params["_q"] = text;
  }

  void addFilterLikeField(FilterHandle* filter, string field, string value)
  {
    filter->params[field + "-lk"] = value;
  }

  void addFilterNotLikeField(FilterHandle* filter, string field, string value)
  {
    filter->params[field + "-not-lk"] = value;
  }

  void addFilterInField(FilterHandle* filter, string field, string value)
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

  void addFilterNotInField(FilterHandle* filter, string field, string value)
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

  void addFilterMinField(FilterHandle* filter, string field, double value)
  {
    filter->params[field + "-min"] = toString(value);
  }

  void addFilterMaxField(FilterHandle* filter, string field, double value)
  {
    filter->params[field + "-max"] = toString(value);
  }

  void addFilterSmallerThanField(FilterHandle* filter, string field, double value)
  {
    filter->params[field + "-st"] = toString(value);
  }

  void addFilterGreaterThanField(FilterHandle* filter, string field, double value)
  {
    filter->params[field + "-gt"] = toString(value);
  }

  void addFilterNotEqualField(FilterHandle* filter, string field, string value)
  {
    filter->params[field + "-not"] = value;
  }
}
