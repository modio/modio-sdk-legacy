#ifndef MODIO_FILTER_H
#define MODIO_FILTER_H

#include <map>
#include "Globals.h"
#include "Utility.h"

using namespace std;

namespace modio
{
  struct Filter
  {
    map<string,string> params;
  };

  string getFilterString(Filter* filter);

  void setFilterSort(Filter* filter, string field, bool ascending);
  void setFilterLimit(Filter* filter, int limit);
  void setFilterOffset(Filter* filter, int offset);
  void setFilterCursor(Filter* filter, int cursor);
  void setFilterFullTextSearch(Filter* filter, string text);
  void addFilterLikeField(Filter* filter, string field, string value);
  void addFilterNotLikeField(Filter* filter, string field, string value);
  void addFilterInField(Filter* filter, string field, string value);
  void addFilterNotInField(Filter* filter, string field, string value);
  void addFilterMinField(Filter* filter, string field, double value);
  void addFilterMaxField(Filter* filter, string field, double value);
  void addFilterSmallerThanField(Filter* filter, string field, double value);
  void addFilterGreaterThanField(Filter* filter, string field, double value);
  void addFilterNotEqualField(Filter* filter, string field, string value);
}

#endif
