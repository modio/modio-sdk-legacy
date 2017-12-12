#include "instance/handlers/FilterHandler.h"

namespace modio
{
  FilterHandler::FilterHandler()
  {
    this->filter = new ModioFilterHandler;
    modioInitFilter(this->filter);
  }

  void FilterHandler::setSort(const std::string& field, bool ascending)
  {
    modioSetFilterSort(this->filter, (char*)field.c_str(), ascending);
  }

  void FilterHandler::setLimit(u32 limit)
  {
    modioSetFilterLimit(this->filter, limit);
  }

  void FilterHandler::setOffset(u32 offset)
  {
    modioSetFilterOffset(this->filter, offset);
  }

  void FilterHandler::setCursor(u32 cursor)
  {
    modioSetFilterCursor(this->filter, cursor);
  }

  void FilterHandler::setFullTextSearch(const std::string& text)
  {
    modioSetFilterFullTextSearch(this->filter, (char*)text.c_str());
  }

  void FilterHandler::addFieldValue(const std::string& field, const std::string& value)
  {
    modioAddFilterFieldValue(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterHandler::addLikeField(const std::string& field, const std::string& value)
  {
    modioAddFilterLikeField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterHandler::addNotLikeField(const std::string& field, const std::string& value)
  {
    modioAddFilterNotLikeField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterHandler::addInField(const std::string& field, const std::string& value)
  {
    modioAddFilterInField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterHandler::addNotInField(const std::string& field, const std::string& value)
  {
    modioAddFilterNotInField(this->filter, (char*)field.c_str(), (char*)value.c_str());
  }

  void FilterHandler::addMinField(const std::string& field, double value)
  {
    modioAddFilterMinField(this->filter, (char*)field.c_str(), value);
  }

  void FilterHandler::addMaxField(const std::string& field, double value)
  {
    modioAddFilterMaxField(this->filter, (char*)field.c_str(), value);
  }

  void FilterHandler::addSmallerThanField(const std::string& field, double value)
  {
    modioAddFilterSmallerThanField(this->filter, (char*)field.c_str(), value);
  }

  void FilterHandler::addGreaterThanField(const std::string& field, double value)
  {
    modioAddFilterGreaterThanField(this->filter, (char*)field.c_str(), value);
  }

  void FilterHandler::addNotEqualField(const std::string& field, const std::string& value)
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
