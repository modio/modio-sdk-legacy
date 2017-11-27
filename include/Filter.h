#ifndef MODIO_FILTER_H
#define MODIO_FILTER_H

#include <map>
#include "Globals.h"
#include "Utility.h"

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
    ModioListNode* field_value_list;
    ModioListNode* like_list;
    ModioListNode* not_like_list;
    ModioListNode* in_list;
    ModioListNode* not_in_list;
    ModioListNode* min_list;
    ModioListNode* max_list;
    ModioListNode* smaller_than_list;
    ModioListNode* greater_than_list;
    ModioListNode* not_equal_list;
  };

  void MODIO_DLL modioInitFilter(ModioFilter* filter);
  void MODIO_DLL modioSetFilterSort(ModioFilter* filter, char* field, bool ascending);
  void MODIO_DLL modioSetFilterLimit(ModioFilter* filter, int limit);
  void MODIO_DLL modioSetFilterOffset(ModioFilter* filter, int offset);
  void MODIO_DLL modioSetFilterCursor(ModioFilter* filter, int cursor);
  void MODIO_DLL modioSetFilterFullTextSearch(ModioFilter* filter, char* text);
  void MODIO_DLL modioAddFilterFieldValue(ModioFilter* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterLikeField(ModioFilter* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterNotLikeField(ModioFilter* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterInField(ModioFilter* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterNotInField(ModioFilter* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterMinField(ModioFilter* filter, char* field, double value);
  void MODIO_DLL modioAddFilterMaxField(ModioFilter* filter, char* field, double value);
  void MODIO_DLL modioAddFilterSmallerThanField(ModioFilter* filter, char* field, double value);
  void MODIO_DLL modioAddFilterGreaterThanField(ModioFilter* filter, char* field, double value);
  void MODIO_DLL modioAddFilterNotEqualField(ModioFilter* filter, char* field, char* value);
  void MODIO_DLL modioFreeFilter(ModioFilter* filter);
}

namespace modio
{
  std::string getFilterString(ModioFilter* filter);
}

#endif
