#include "c/creators/ModioFilterCreator.h"


namespace modio
{
  std::string getField(std::string str)
  {
    return str.substr(0,str.find("="));
  }

  bool appendIfExists(ModioListNode* list, std::string field, std::string value)
  {
    for(ModioListNode* iterator = list; iterator != NULL; iterator = iterator->next)
    {
      if(getField(iterator->value) == field)
      {
        char* old_value = iterator->value;
        std::string appended_value = std::string(iterator->value) + "," + value;
        iterator->value = new char[appended_value.size() + 1];
        strcpy(iterator->value, appended_value.c_str());
        delete[] old_value;
        return true;
      }
    }
    return false;
  }

  bool replaceIfExists(ModioListNode* list, std::string field, std::string value)
  {
    for(ModioListNode* iterator = list; iterator != NULL; iterator = iterator->next)
    {
      if(getField(iterator->value) == field)
      {
        char* old_value = iterator->value;
        std::string replaced_value = field + "=" + value;
        iterator->value = new char[replaced_value.size() + 1];
        strcpy(iterator->value, replaced_value.c_str());
        delete[] old_value;
        return true;
      }
    }
    return false;
  }

  ModioListNode* addNewNode(ModioListNode* list, std::string value)
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
  void modioInitFilter(ModioFilterCreator* filter)
  {
    filter->sort = NULL;
    filter->limit = NULL;
    filter->offset = NULL;
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
    filter->cache_max_age_seconds = 0;
  }

  void modioSetFilterSort(ModioFilterCreator* filter, char const* field, bool ascending)
  {
    if(filter->sort)
      delete[] filter->sort;
    std::string ascending_str = "";
    if(!ascending)
      ascending_str = "-";
    std::string sort_str = std::string("_sort=") + ascending_str + field;
    filter->sort = new char[sort_str.size() + 1];
    strcpy(filter->sort, sort_str.c_str());
  }

  void modioSetFilterLimit(ModioFilterCreator* filter, u32 limit)
  {
    if(filter->limit)
      delete[] filter->limit;
    std::string limit_str = std::string("_limit=") + modio::toString(limit);
    filter->limit = new char[limit_str.size() + 1];
    strcpy(filter->limit, limit_str.c_str());
  }

  void modioSetFilterOffset(ModioFilterCreator* filter, u32 offset)
  {
    if(filter->offset)
      delete[] filter->offset;
    std::string offset_str = std::string("_offset=") + modio::toString(offset);
    filter->offset = new char[offset_str.size() + 1];
    strcpy(filter->offset, offset_str.c_str());
  }

  void modioSetFilterFullTextSearch(ModioFilterCreator* filter, char const* text)
  {
    if(filter->full_text_search)
      delete[] filter->full_text_search;
    std::string full_text_search_str = std::string("_q=") + text;
    filter->full_text_search = new char[full_text_search_str.size() + 1];
    strcpy(filter->full_text_search, full_text_search_str.c_str());
  }

  void modioSetFilterCacheMaxAgeSeconds(ModioFilterCreator* filter, u32 max_age_seconds)
  {
    filter->cache_max_age_seconds = max_age_seconds;
  }

  void modioAddFilterFieldValue(ModioFilterCreator* filter, char const* field, char const* value)
  {
    if(modio::replaceIfExists(filter->field_value_list, std::string(field) , value))
      return;
    else
      filter->field_value_list = modio::addNewNode(filter->field_value_list, std::string(field) + "=" + value);
  }

  void modioAddFilterLikeField(ModioFilterCreator* filter, char const* field, char const* value)
  {
    if(modio::replaceIfExists(filter->like_list, std::string(field) + "-lk" , value))
      return;
    else
      filter->like_list = modio::addNewNode(filter->like_list, std::string(field) + "-lk=" + value);
  }

  void modioAddFilterNotLikeField(ModioFilterCreator* filter, char const* field, char const* value)
  {
    if(modio::replaceIfExists(filter->not_like_list, std::string(field) + "-not-lk" , value))
      return;
    else
      filter->not_like_list = modio::addNewNode(filter->not_like_list, std::string(field) + "-not-lk=" + value);
  }

  void modioAddFilterInField(ModioFilterCreator* filter, char const* field, char const* value)
  {
    if(modio::appendIfExists(filter->in_list, std::string(field) + "-in" , value))
      return;
    else
      filter->in_list = modio::addNewNode(filter->in_list, std::string(field) + "-in=" + value);
  }

  void modioAddFilterNotInField(ModioFilterCreator* filter, char const* field, char const* value)
  {
    if(modio::appendIfExists(filter->not_in_list, std::string(field) + "-not-in" , value))
      return;
    else
      filter->not_in_list = modio::addNewNode(filter->not_in_list, std::string(field) + "-not-in=" + value);
  }

  void modioAddFilterMinField(ModioFilterCreator* filter, char const* field, char const* value)
  {
    if(modio::replaceIfExists(filter->min_list, std::string(field) + "-min" , value))
      return;
    else
      filter->min_list = modio::addNewNode(filter->min_list, std::string(field) + "-min=" + value);
  }

  void modioAddFilterMaxField(ModioFilterCreator* filter, char const* field, char const* value)
  {
    if(modio::replaceIfExists(filter->max_list, std::string(field) + "-max" , value))
      return;
    else
      filter->max_list = modio::addNewNode(filter->max_list, std::string(field) + "-max=" + value);
  }

  void modioAddFilterSmallerThanField(ModioFilterCreator* filter, char const* field, char const* value)
  {
    if(modio::replaceIfExists(filter->smaller_than_list, std::string(field) + "-st" , value))
      return;
    else
      filter->smaller_than_list = modio::addNewNode(filter->smaller_than_list, std::string(field) + "-st=" + value);
  }

  void modioAddFilterGreaterThanField(ModioFilterCreator* filter, char const* field, char const* value)
  {
    if(modio::replaceIfExists(filter->greater_than_list, std::string(field) + "-gt" , value))
      return;
    else
      filter->greater_than_list = modio::addNewNode(filter->greater_than_list, std::string(field) + "-gt=" + value);
  }

  void modioAddFilterNotEqualField(ModioFilterCreator* filter, char const* field, char const* value)
  {
    if(modio::replaceIfExists(filter->not_equal_list, std::string(field) + "-not" , value))
      return;
    else
      filter->not_equal_list = modio::addNewNode(filter->not_equal_list, std::string(field) + "-not=" + value);
  }

  void modioFreeFilter(ModioFilterCreator* filter)
  {
    if(filter->sort)
      delete[] filter->sort;
    if(filter->limit)
      delete[] filter->limit;
    if(filter->offset)
      delete[] filter->offset;
    if(filter->full_text_search)
      delete[] filter->full_text_search;

    if(filter->field_value_list)
      modioFreeNodeList(filter->field_value_list);
    if(filter->like_list)
      modioFreeNodeList(filter->like_list);
    if(filter->not_like_list)
      modioFreeNodeList(filter->not_like_list);
    if(filter->in_list)
      modioFreeNodeList(filter->in_list);
    if(filter->not_in_list)
      modioFreeNodeList(filter->not_in_list);
    if(filter->min_list)
      modioFreeNodeList(filter->min_list);
    if(filter->max_list)
      modioFreeNodeList(filter->max_list);
    if(filter->smaller_than_list)
      modioFreeNodeList(filter->smaller_than_list);
    if(filter->greater_than_list)
      modioFreeNodeList(filter->greater_than_list);
    if(filter->not_equal_list)
      modioFreeNodeList(filter->not_equal_list);
  }
}

namespace modio
{
  std::string addParam(std::string filter_string, char* param)
  {
    if(param)
    {
      if(filter_string != "")
        filter_string += "&";
      filter_string += param;
    }
    return filter_string;
  }

  std::string addParam(std::string filter_string, ModioListNode* param_list)
  {
    for(ModioListNode* iterator = param_list; iterator != NULL; iterator = iterator->next)
    {
      if(filter_string != "")
        filter_string += "&";
      filter_string += iterator->value;
    }
    return filter_string;
  }

  std::string getFilterString(ModioFilterCreator* filter)
  {
    std::string filter_string = "";
    filter_string = addParam(filter_string, filter->sort);
    filter_string = addParam(filter_string, filter->limit);
    filter_string = addParam(filter_string, filter->offset);
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
