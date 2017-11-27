#include "ModIOInstance.h"

namespace modio
{
  Filter::Filter()
  {
    this->filter = new ModioFilter;
    modioInitFilter(this->filter);
  }

  void Filter::setFilterSort(const std::string& field, bool ascending)
  {
    modioSetFilterSort(this->filter, (char*)field.c_str(), ascending);
  }

  void Filter::setFilterLimit(u32 limit)
  {
    modioSetFilterLimit(this->filter, limit);
  }

  void Filter::setFilterOffset(u32 offset)
  {
    modioSetFilterOffset(this->filter, offset);
  }

  void Filter::setFilterCursor(u32 cursor)
  {
    modioSetFilterCursor(this->filter, cursor);
  }

  void Filter::setFilterFullTextSearch(const std::string& text)
  {
    modioSetFilterFullTextSearch(this->filter, (char*)text.c_str());
  }

  void Filter::addFilterFieldValue(const std::string& field, const std::string& value)
  {
    modioAddFilterFieldValue(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void Filter::addFilterLikeField(const std::string& field, const std::string& value)
  {
    modioAddFilterLikeField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void Filter::addFilterNotLikeField(const std::string& field, const std::string& value)
  {
    modioAddFilterNotLikeField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void Filter::addFilterInField(const std::string& field, const std::string& value)
  {
    modioAddFilterInField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void Filter::addFilterNotInField(const std::string& field, const std::string& value)
  {
    modioAddFilterNotInField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void Filter::addFilterMinField(const std::string& field, double value)
  {
    modioAddFilterMinField(this->filter, (char*)field.c_str(), value);
  }

  void Filter::addFilterMaxField(const std::string& field, double value)
  {
    modioAddFilterMaxField(this->filter, (char*)field.c_str(), value);
  }

  void Filter::addFilterSmallerThanField(const std::string& field, double value)
  {
    modioAddFilterSmallerThanField(this->filter, (char*)field.c_str(), value);
  }

  void Filter::addFilterGreaterThanField(const std::string& field, double value)
  {
    modioAddFilterGreaterThanField(this->filter, (char*)field.c_str(), value);
  }

  void Filter::addFilterNotEqualField(const std::string& field, const std::string& value)
  {
    modioAddFilterNotEqualField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  ModioFilter* Filter::getFilter()
  {
    return this->filter;
  }

  Filter::~Filter()
  {
    modioFreeFilter(this->filter);
  }
}
