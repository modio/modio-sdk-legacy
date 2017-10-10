#ifndef MODIO_FILTER_H
#define MODIO_FILTER_H

#include <map>
#include "Globals.h"
#include "Utility.h"

using namespace std;

#ifdef WINDOWS
#  ifdef BUILDING_MODIO_DLL
#    define MODIO_DLL __declspec(dllexport)
#  else
#    define MODIO_DLL __declspec(dllimport)
#  endif
#else
#  define MODIO_DLL
#endif

namespace modio
{
  struct Filter
  {
    map<string,string> params;
  };

  string getFilterString(Filter* filter);

  void MODIO_DLL setFilterSort(Filter* filter, string field, bool ascending);
  void MODIO_DLL setFilterLimit(Filter* filter, int limit);
  void MODIO_DLL setFilterOffset(Filter* filter, int offset);
  void MODIO_DLL setFilterCursor(Filter* filter, int cursor);
  void MODIO_DLL setFilterFullTextSearch(Filter* filter, string text);
  void MODIO_DLL addFilterLikeField(Filter* filter, string field, string value);
  void MODIO_DLL addFilterNotLikeField(Filter* filter, string field, string value);
  void MODIO_DLL addFilterInField(Filter* filter, string field, string value);
  void MODIO_DLL addFilterNotInField(Filter* filter, string field, string value);
  void MODIO_DLL addFilterMinField(Filter* filter, string field, double value);
  void MODIO_DLL addFilterMaxField(Filter* filter, string field, double value);
  void MODIO_DLL addFilterSmallerThanField(Filter* filter, string field, double value);
  void MODIO_DLL addFilterGreaterThanField(Filter* filter, string field, double value);
  void MODIO_DLL addFilterNotEqualField(Filter* filter, string field, string value);
}

#endif
