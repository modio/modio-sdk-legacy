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

extern "C"
{
  struct Filter
  {
    char* sort;
    char* limit;
    char* offset;
    char* cursor;
    char* full_text_search;
    char* like;
    char* not_like;
    char* in;
    char* not_in;
    char* min;
    char* max;
    char* smaller_than;
    char* greater_than;
    char* not_equal;
  };

  string getFilterString(Filter* filter);

  void MODIO_DLL initFilter(Filter* filter);
  void MODIO_DLL setFilterSort(Filter* filter, char* field, bool ascending);
  void MODIO_DLL setFilterLimit(Filter* filter, int limit);
  void MODIO_DLL setFilterOffset(Filter* filter, int offset);
  void MODIO_DLL setFilterCursor(Filter* filter, int cursor);
  void MODIO_DLL setFilterFullTextSearch(Filter* filter, char* text);
  void MODIO_DLL addFilterLikeField(Filter* filter, char* field, char* value);
  void MODIO_DLL addFilterNotLikeField(Filter* filter, char* field, char* value);
  void MODIO_DLL addFilterInField(Filter* filter, char* field, char* value);
  void MODIO_DLL addFilterNotInField(Filter* filter, char* field, char* value);
  void MODIO_DLL addFilterMinField(Filter* filter, char* field, double value);
  void MODIO_DLL addFilterMaxField(Filter* filter, char* field, double value);
  void MODIO_DLL addFilterSmallerThanField(Filter* filter, char* field, double value);
  void MODIO_DLL addFilterGreaterThanField(Filter* filter, char* field, double value);
  void MODIO_DLL addFilterNotEqualField(Filter* filter, char* field, char* value);
}

#endif
