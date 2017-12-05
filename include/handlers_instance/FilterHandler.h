#include "ModIOSDK.h"

namespace modio
{
  class MODIO_DLL FilterHandler
  {
    ModioFilterHandler* filter;
  public:
    FilterHandler();
    void setFilterSort(const std::string& field, bool ascending);
    void setFilterLimit(u32 limit);
    void setFilterOffset(u32 offset);
    void setFilterCursor(u32 cursor);
    void setFilterFullTextSearch(const std::string& text);
    void addFilterFieldValue(const std::string& field, const std::string& value);
    void addFilterLikeField(const std::string& field, const std::string& value);
    void addFilterNotLikeField(const std::string& field, const std::string& value);
    void addFilterInField(const std::string& field, const std::string& value);
    void addFilterNotInField(const std::string& field, const std::string& value);
    void addFilterMinField(const std::string& field, double value);
    void addFilterMaxField(const std::string& field, double value);
    void addFilterSmallerThanField(const std::string& field, double value);
    void addFilterGreaterThanField(const std::string& field, double value);
    void addFilterNotEqualField(const std::string& field, const std::string& value);
    ModioFilterHandler* getFilter();
    ~FilterHandler();
  };
}
