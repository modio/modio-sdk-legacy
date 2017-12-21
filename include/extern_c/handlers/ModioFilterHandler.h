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
  struct ModioFilterHandler
  {
    char* sort;
    char* limit;
    char* offset;
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

  void MODIO_DLL modioInitFilter(ModioFilterHandler* filter);
  void MODIO_DLL modioSetFilterSort(ModioFilterHandler* filter, char* field, bool ascending);
  void MODIO_DLL modioSetFilterLimit(ModioFilterHandler* filter, int limit);
  void MODIO_DLL modioSetFilterOffset(ModioFilterHandler* filter, int offset);
  void MODIO_DLL modioSetFilterFullTextSearch(ModioFilterHandler* filter, char* text);
  void MODIO_DLL modioAddFilterFieldValue(ModioFilterHandler* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterLikeField(ModioFilterHandler* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterNotLikeField(ModioFilterHandler* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterInField(ModioFilterHandler* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterNotInField(ModioFilterHandler* filter, char* field, char* value);
  void MODIO_DLL modioAddFilterMinField(ModioFilterHandler* filter, char* field, double value);
  void MODIO_DLL modioAddFilterMaxField(ModioFilterHandler* filter, char* field, double value);
  void MODIO_DLL modioAddFilterSmallerThanField(ModioFilterHandler* filter, char* field, double value);
  void MODIO_DLL modioAddFilterGreaterThanField(ModioFilterHandler* filter, char* field, double value);
  void MODIO_DLL modioAddFilterNotEqualField(ModioFilterHandler* filter, char* field, char* value);
  void MODIO_DLL modioFreeFilter(ModioFilterHandler* filter);
}

namespace modio
{
  std::string getFilterString(ModioFilterHandler* filter);
}

#endif
