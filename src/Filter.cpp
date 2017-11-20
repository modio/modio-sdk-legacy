#include "Filter.h"


namespace modio
{
  string getField(string str)
  {
    return str.substr(0,str.find("="));
  }

  bool appendIfExists(ModioListNode* list, string field, string value)
  {
    for(ModioListNode* iterator = list; iterator != NULL; iterator = iterator->next)
    {
      if(getField(iterator->value) == field)
      {
        char* old_value = iterator->value;
        string appended_value = string(iterator->value) + "," + value;
        iterator->value = new char[appended_value.size() + 1];
        strcpy(iterator->value,appended_value.c_str());
        delete old_value;
        return true;
      }
    }
    return false;
  }

  bool replaceIfExists(ModioListNode* list, string field, string value)
  {
    for(ModioListNode* iterator = list; iterator != NULL; iterator = iterator->next)
    {
      if(getField(iterator->value) == field)
      {
        char* old_value = iterator->value;
        string replaced_value = field + "=" + value;
        iterator->value = new char[replaced_value.size() + 1];
        strcpy(iterator->value,replaced_value.c_str());
        delete old_value;
        return true;
      }
    }
    return false;
  }

  ModioListNode* addNewNode(ModioListNode* list, string value)
  {
    ModioListNode* node = new ModioListNode;
    node->value = new char[value.size() + 1];
    strcpy(node->value, value.c_str());
    node->next = list;

    return node;
  }
}

extern "C"
{
  void modioInitFilter(ModioFilter* filter)
  {
    filter->sort = NULL;
    filter->limit = NULL;
    filter->offset = NULL;
    filter->cursor = NULL;
    filter->full_text_search = NULL;
    filter->field_value_list = NULL;
    filter->like_list = NULL;
    filter->not_like_list = NULL;
    filter->in_list = NULL;
    filter->not_in_list = NULL;
    filter->min_list = NULL;
    filter->max_list = NULL;
    filter->smaller_than_list = NULL;
    filter->greater_than_list = NULL;
    filter->not_equal_list = NULL;
  }

  void modioSetFilterSort(ModioFilter* filter, char* field, bool ascending)
  {
    if(filter->sort)
      delete[] filter->sort;
    string ascending_str = "";
    if(!ascending)
      ascending_str = "-";
    string sort_str = string("_sort=") + ascending_str + field;
    filter->sort = new char[sort_str.size() + 1];
    strcpy(filter->sort, sort_str.c_str());
  }

  void modioSetFilterLimit(ModioFilter* filter, int limit)
  {
    if(filter->limit)
      delete[] filter->limit;
    string limit_str = string("_limit=") + modio::toString(limit);
    filter->limit = new char[limit_str.size() + 1];
    strcpy(filter->limit, limit_str.c_str());
  }

  void modioSetFilterOffset(ModioFilter* filter, int offset)
  {
    if(filter->offset)
      delete[] filter->offset;
    string offset_str = string("_offset=") + modio::toString(offset);
    filter->offset = new char[offset_str.size() + 1];
    strcpy(filter->offset, offset_str.c_str());
  }

  void modioSetFilterCursor(ModioFilter* filter, int cursor)
  {
    if(filter->cursor)
      delete[] filter->cursor;
    string cursor_str = string("_cursor=") + modio::toString(cursor);
    filter->cursor = new char[cursor_str.size() + 1];
    strcpy(filter->cursor, cursor_str.c_str());
  }

  void modioSetFilterFullTextSearch(ModioFilter* filter, char* text)
  {
    if(filter->full_text_search)
      delete[] filter->full_text_search;
    string full_text_search_str = string("_q=") + text;
    filter->full_text_search = new char[full_text_search_str.size() + 1];
    strcpy(filter->full_text_search, full_text_search_str.c_str());
  }

  void modioAddFilterFieldValue(ModioFilter* filter, char* field, char* value)
  {
    if(modio::replaceIfExists(filter->field_value_list, string(field) , value))
      return;
    else
      filter->field_value_list = modio::addNewNode(filter->field_value_list, string(field) + "=" + value);
  }

  void modioAddFilterLikeField(ModioFilter* filter, char* field, char* value)
  {
    if(modio::replaceIfExists(filter->like_list, string(field) + "-lk" , value))
      return;
    else
      filter->like_list = modio::addNewNode(filter->like_list, string(field) + "-lk=" + value);
  }

  void modioAddFilterNotLikeField(ModioFilter* filter, char* field, char* value)
  {
    if(modio::replaceIfExists(filter->not_like_list, string(field) + "-not-lk" , value))
      return;
    else
      filter->not_like_list = modio::addNewNode(filter->not_like_list, string(field) + "-not-lk=" + value);
  }

  void modioAddFilterInField(ModioFilter* filter, char* field, char* value)
  {
    if(modio::appendIfExists(filter->in_list, string(field) + "-in" , value))
      return;
    else
      filter->in_list = modio::addNewNode(filter->in_list, string(field) + "-in=" + value);
  }

  void modioAddFilterNotInField(ModioFilter* filter, char* field, char* value)
  {
    if(modio::appendIfExists(filter->not_in_list, string(field) + "-not-in" , value))
      return;
    else
      filter->not_in_list = modio::addNewNode(filter->not_in_list, string(field) + "-not-in=" + value);
  }

  void modioAddFilterMinField(ModioFilter* filter, char* field, double value)
  {
    if(modio::replaceIfExists(filter->min_list, string(field) + "-min" , modio::toString(value)))
      return;
    else
      filter->min_list = modio::addNewNode(filter->min_list, string(field) + "-min=" + modio::toString(value));
  }

  void modioAddFilterMaxField(ModioFilter* filter, char* field, double value)
  {
    if(modio::replaceIfExists(filter->max_list, string(field) + "-max" , modio::toString(value)))
      return;
    else
      filter->max_list = modio::addNewNode(filter->max_list, string(field) + "-max=" + modio::toString(value));
  }

  void modioAddFilterSmallerThanField(ModioFilter* filter, char* field, double value)
  {
    if(modio::replaceIfExists(filter->smaller_than_list, string(field) + "-st" , modio::toString(value)))
      return;
    else
      filter->smaller_than_list = modio::addNewNode(filter->smaller_than_list, string(field) + "-st=" + modio::toString(value));
  }

  void modioAddFilterGreaterThanField(ModioFilter* filter, char* field, double value)
  {
    if(modio::replaceIfExists(filter->greater_than_list, string(field) + "-gt" , modio::toString(value)))
      return;
    else
      filter->greater_than_list = modio::addNewNode(filter->greater_than_list, string(field) + "-gt=" + modio::toString(value));
  }

  void modioAddFilterNotEqualField(ModioFilter* filter, char* field, char* value)
  {
    if(modio::replaceIfExists(filter->not_equal_list, string(field) + "-not" , value))
      return;
    else
      filter->not_equal_list = modio::addNewNode(filter->not_equal_list, string(field) + "-not=" + value);
  }

  void modioFreeFilter(ModioFilter* filter)
  {
    delete filter->sort;
    delete filter->limit;
    delete filter->offset;
    delete filter->cursor;
    delete filter->full_text_search;

    modioFreeNodeList(filter->like_list);
    modioFreeNodeList(filter->not_like_list);
    modioFreeNodeList(filter->in_list);
    modioFreeNodeList(filter->not_in_list);
    modioFreeNodeList(filter->min_list);
    modioFreeNodeList(filter->max_list);
    modioFreeNodeList(filter->smaller_than_list);
    modioFreeNodeList(filter->greater_than_list);
    modioFreeNodeList(filter->not_equal_list);
  }
}

namespace modio
{
  string addParam(string filter_string, char* param)
  {
    if(param)
    {
      if(filter_string != "")
        filter_string += "&";
      filter_string += param;
    }
    return filter_string;
  }

  string addParam(string filter_string, ModioListNode* param_list)
  {
    for(ModioListNode* iterator = param_list; iterator != NULL; iterator = iterator->next)
    {
      if(filter_string != "")
        filter_string += "&";
      filter_string += iterator->value;
    }
    return filter_string;
  }

  string getFilterString(ModioFilter* filter)
  {
    string filter_string = "";
    filter_string = addParam(filter_string, filter->sort);
    filter_string = addParam(filter_string, filter->limit);
    filter_string = addParam(filter_string, filter->offset);
    filter_string = addParam(filter_string, filter->cursor);
    filter_string = addParam(filter_string, filter->full_text_search);

    filter_string = addParam(filter_string, filter->field_value_list);
    filter_string = addParam(filter_string, filter->like_list);
    filter_string = addParam(filter_string, filter->not_like_list);
    filter_string = addParam(filter_string, filter->in_list);
    filter_string = addParam(filter_string, filter->not_in_list);
    filter_string = addParam(filter_string, filter->min_list);
    filter_string = addParam(filter_string, filter->max_list);
    filter_string = addParam(filter_string, filter->smaller_than_list);
    filter_string = addParam(filter_string, filter->greater_than_list);
    filter_string = addParam(filter_string, filter->not_equal_list);
    return filter_string;
  }
}
