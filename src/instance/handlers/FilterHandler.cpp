#include "instance/handlers/FilterHandler.h"

namespace modio
{
  FilterHandler::FilterHandler()
  {
    this->filter = new ModioFilterHandler;
    modioInitFilter(this->filter);
  }

  void FilterHandler::setFilterSort(const std::string& field, bool ascending)
  {
    modioSetFilterSort(this->filter, (char*)field.c_str(), ascending);
  }

  void FilterHandler::setFilterLimit(u32 limit)
  {
    modioSetFilterLimit(this->filter, limit);
  }

  void FilterHandler::setFilterOffset(u32 offset)
  {
    modioSetFilterOffset(this->filter, offset);
  }

  void FilterHandler::setFilterCursor(u32 cursor)
  {
    modioSetFilterCursor(this->filter, cursor);
  }

  void FilterHandler::setFilterFullTextSearch(const std::string& text)
  {
    modioSetFilterFullTextSearch(this->filter, (char*)text.c_str());
  }

  void FilterHandler::addFilterFieldValue(const std::string& field, const std::string& value)
  {
    modioAddFilterFieldValue(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterHandler::addFilterLikeField(const std::string& field, const std::string& value)
  {
    modioAddFilterLikeField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterHandler::addFilterNotLikeField(const std::string& field, const std::string& value)
  {
    modioAddFilterNotLikeField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterHandler::addFilterInField(const std::string& field, const std::string& value)
  {
    modioAddFilterInField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterHandler::addFilterNotInField(const std::string& field, const std::string& value)
  {
    modioAddFilterNotInField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterHandler::addFilterMinField(const std::string& field, double value)
  {
    modioAddFilterMinField(this->filter, (char*)field.c_str(), value);
  }

  void FilterHandler::addFilterMaxField(const std::string& field, double value)
  {
    modioAddFilterMaxField(this->filter, (char*)field.c_str(), value);
  }

  void FilterHandler::addFilterSmallerThanField(const std::string& field, double value)
  {
    modioAddFilterSmallerThanField(this->filter, (char*)field.c_str(), value);
  }

  void FilterHandler::addFilterGreaterThanField(const std::string& field, double value)
  {
    modioAddFilterGreaterThanField(this->filter, (char*)field.c_str(), value);
  }

  void FilterHandler::addFilterNotEqualField(const std::string& field, const std::string& value)
  {
    modioAddFilterNotEqualField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  ModioFilterHandler* FilterHandler::getFilter()
  {
    return this->filter;
  }

  FilterHandler::~FilterHandler()
  {
    modioFreeFilter(this->filter);
  }
}
