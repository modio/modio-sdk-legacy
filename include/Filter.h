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
  struct ModioFilter
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

  void MODIO_DLL modioInitFilter(ModioFilter* filter);
  void MODIO_DLL modioSetFilterSort(ModioFilter* filter, char* field, bool ascending);
  void MODIO_DLL modioSetFilterLimit(ModioFilter* filter, int limit);
  void MODIO_DLL modioSetFilterOffset(ModioFilter* filter, int offset);
  void MODIO_DLL modioSetFilterCursor(ModioFilter* filter, int cursor);
  void MODIO_DLL modioSetFilterFullTextSearch(ModioFilter* filter, char* text);
  void MODIO_DLL modioAddFilterLikeField(ModioFilter* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterNotLikeField(ModioFilter* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterInField(ModioFilter* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterNotInField(ModioFilter* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterMinField(ModioFilter* filter, char* field, double value);
  void MODIO_DLL modioAddFilterMaxField(ModioFilter* filter, char* field, double value);
  void MODIO_DLL modioAddFilterSmallerThanField(ModioFilter* filter, char* field, double value);
  void MODIO_DLL modioAddFilterGreaterThanField(ModioFilter* filter, char* field, double value);
  void MODIO_DLL modioAddFilterNotEqualField(ModioFilter* filter, char* field, char* value);
}

namespace modio
{
  string getFilterString(ModioFilter* filter);
}

#endif
