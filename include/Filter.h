#ifndef MOD_FILTER_METHODS
#define MOD_FILTER_METHODS

#include <map>
#include "Globals.h"
#include "Utility.h"

using namespace std;

namespace modworks
{
  struct FilterHandle
  {
    map<string,string> params;
  };

  void addFilterField(FilterHandle* filter, string field);
  void setFilterSort(FilterHandle* filter, string field, bool ascending);
  void setFilterLimit(FilterHandle* filter, int limit);
  void setFilterOffset(FilterHandle* filter, int offset);
  void setFilterFullTextSearch(FilterHandle* filter, string text);
  void addFilterLikeField(FilterHandle* filter, string field, string value);
  void addFilterNotLikeField(FilterHandle* filter, string field, string value);
  void addFilterInField(FilterHandle* filter, string field, string value);
  void addFilterNotInField(FilterHandle* filter, string field, string value);
  void addFilterMinField(FilterHandle* filter, string field, double value);
  void addFilterMaxField(FilterHandle* filter, string field, double value);
  void addFilterSmallerThanField(FilterHandle* filter, string field, double value);
  void addFilterGreaterThanField(FilterHandle* filter, string field, double value);
  void addFilterNotEqualField(FilterHandle* filter, string field, string value);
}

#endif
