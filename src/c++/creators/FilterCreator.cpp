#include "c++/creators/FilterCreator.h"

namespace modio
{
  FilterCreator::FilterCreator()
  {
    filter = new ModioFilterCreator;
    modioInitFilter(filter);
  }

  void FilterCreator::setSort(const std::string& field, bool ascending)
  {
    modioSetFilterSort(filter, field.c_str(), ascending);
  }

  void FilterCreator::setLimit(u32 limit)
  {
    modioSetFilterLimit(filter, limit);
  }

  void FilterCreator::setOffset(u32 offset)
  {
    modioSetFilterOffset(filter, offset);
  }

  void FilterCreator::setFullTextSearch(const std::string& text)
  {
    modioSetFilterFullTextSearch(filter, text.c_str());
  }

  void FilterCreator::setCacheMaxAgeSeconds(u32 max_age_seconds)
  {
    modioSetFilterCacheMaxAgeSeconds(filter, max_age_seconds);
  }

  void FilterCreator::addFieldValue(const std::string& field, const std::string& value)
  {
    modioAddFilterFieldValue(filter, field.c_str(), value.c_str());
  }

  void FilterCreator::addLikeField(const std::string& field, const std::string& value)
  {
    modioAddFilterLikeField(filter, field.c_str(), value.c_str());
  }

  void FilterCreator::addNotLikeField(const std::string& field, const std::string& value)
  {
    modioAddFilterNotLikeField(filter, field.c_str(), value.c_str());
  }

  void FilterCreator::addInField(const std::string& field, const std::string& value)
  {
    modioAddFilterInField(filter, field.c_str(), value.c_str());
  }

  void FilterCreator::addNotInField(const std::string& field, const std::string& value)
  {
    modioAddFilterNotInField(filter, field.c_str(), value.c_str());
  }

  void FilterCreator::addMinField(const std::string& field, const std::string& value)
  {
    modioAddFilterMinField(filter, field.c_str(), value.c_str());
  }

  void FilterCreator::addMaxField(const std::string& field, const std::string& value)
  {
    modioAddFilterMaxField(filter, field.c_str(), value.c_str());
  }

  void FilterCreator::addSmallerThanField(const std::string& field, const std::string& value)
  {
    modioAddFilterSmallerThanField(filter, field.c_str(), value.c_str());
  }

  void FilterCreator::addGreaterThanField(const std::string& field, const std::string& value)
  {
    modioAddFilterGreaterThanField(filter, field.c_str(), value.c_str());
  }

  void FilterCreator::addNotEqualField(const std::string& field, const std::string& value)
  {
    modioAddFilterNotEqualField(filter, field.c_str(), value.c_str());
  }

  ModioFilterCreator* FilterCreator::getFilter()
  {
    return filter;
  }

  FilterCreator::~FilterCreator()
  {
    modioFreeFilter(filter);
	  delete filter;
  }
}
