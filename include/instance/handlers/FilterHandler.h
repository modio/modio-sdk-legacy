#ifndef MODIO_FILTERHANDLER_H
#define MODIO_FILTERHANDLER_H

#include "extern_c/handlers/ModioFilterHandler.h"

namespace modio
{
  class MODIO_DLL FilterHandler
  {
    ModioFilterHandler* filter;
  public:
    FilterHandler();
    void setSort(const std::string& field, bool ascending);
    void setLimit(u32 limit);
    void setOffset(u32 offset);
    void setFullTextSearch(const std::string& text);
    void addFieldValue(const std::string& field, const std::string& value);
    void addLikeField(const std::string& field, const std::string& value);
    void addNotLikeField(const std::string& field, const std::string& value);
    void addInField(const std::string& field, const std::string& value);
    void addNotInField(const std::string& field, const std::string& value);
    void addMinField(const std::string& field, double value);
    void addMaxField(const std::string& field, double value);
    void addSmallerThanField(const std::string& field, double value);
    void addGreaterThanField(const std::string& field, double value);
    void addNotEqualField(const std::string& field, const std::string& value);
    ModioFilterHandler* getFilter();
    ~FilterHandler();
  };
}

#endif
