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

  MODIO_DLL void setFilterSort(Filter* filter, string field, bool ascending);
  MODIO_DLL void setFilterLimit(Filter* filter, int limit);
  MODIO_DLL void setFilterOffset(Filter* filter, int offset);
  MODIO_DLL void setFilterCursor(Filter* filter, int cursor);
  MODIO_DLL void setFilterFullTextSearch(Filter* filter, string text);
  MODIO_DLL void addFilterLikeField(Filter* filter, string field, string value);
  MODIO_DLL void addFilterNotLikeField(Filter* filter, string field, string value);
  MODIO_DLL void addFilterInField(Filter* filter, string field, string value);
  MODIO_DLL void addFilterNotInField(Filter* filter, string field, string value);
  MODIO_DLL void addFilterMinField(Filter* filter, string field, double value);
  MODIO_DLL void addFilterMaxField(Filter* filter, string field, double value);
  MODIO_DLL void addFilterSmallerThanField(Filter* filter, string field, double value);
  MODIO_DLL void addFilterGreaterThanField(Filter* filter, string field, double value);
  MODIO_DLL void addFilterNotEqualField(Filter* filter, string field, string value);
}

#endif
