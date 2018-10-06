#include "c++/creators/FilterCreator.h"

namespace modio
{
  FilterCreator::FilterCreator()
  {
    this->filter = new ModioFilterCreator;
    modioInitFilter(this->filter);
  }

  void FilterCreator::setSort(const std::string& field, bool ascending)
  {
    modioSetFilterSort(this->filter, (char*)field.c_str(), ascending);
  }

  void FilterCreator::setLimit(u32 limit)
  {
    modioSetFilterLimit(this->filter, limit);
  }

  void FilterCreator::setOffset(u32 offset)
  {
    modioSetFilterOffset(this->filter, offset);
  }

  void FilterCreator::setFullTextSearch(const std::string& text)
  {
    modioSetFilterFullTextSearch(this->filter, (char*)text.c_str());
  }

  void FilterCreator::setCacheMaxAgeSeconds(u32 max_age_seconds)
  {
    modioSetFilterCacheMaxAgeSeconds(this->filter, max_age_seconds);
  }

  void FilterCreator::addFieldValue(const std::string& field, const std::string& value)
  {
    modioAddFilterFieldValue(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterCreator::addLikeField(const std::string& field, const std::string& value)
  {
    modioAddFilterLikeField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterCreator::addNotLikeField(const std::string& field, const std::string& value)
  {
    modioAddFilterNotLikeField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterCreator::addInField(const std::string& field, const std::string& value)
  {
    modioAddFilterInField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterCreator::addNotInField(const std::string& field, const std::string& value)
  {
    modioAddFilterNotInField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterCreator::addMinField(const std::string& field, const std::string& value)
  {
    modioAddFilterMinField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterCreator::addMaxField(const std::string& field, const std::string& value)
  {
    modioAddFilterMaxField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterCreator::addSmallerThanField(const std::string& field, const std::string& value)
  {
    modioAddFilterSmallerThanField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterCreator::addGreaterThanField(const std::string& field, const std::string& value)
  {
    modioAddFilterGreaterThanField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterCreator::addNotEqualField(const std::string& field, const std::string& value)
  {
    modioAddFilterNotEqualField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  ModioFilterCreator* FilterCreator::getFilter()
  {
    return this->filter;
  }

  FilterCreator::~FilterCreator()
  {
    modioFreeFilter(this->filter);
	delete this->filter;
  }
}
