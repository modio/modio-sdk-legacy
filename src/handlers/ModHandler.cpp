#include "handlers/ModHandler.h"

namespace modio
{
  void ModHandler::setLogoPath(string logo_path)
  {
    this->curlform_files["logo"] = logo_path;
  }

  void ModHandler::setName(string name)
  {
    this->curlform_copycontents["name"] = name;
  }

  void ModHandler::setHomepage(string homepage)
  {
    this->curlform_copycontents["homepage"] = homepage;
  }

  void ModHandler::setSummary(string summary)
  {
    this->curlform_copycontents["summary"] = summary;
  }

  void ModHandler::setPrice(double price)
  {
    this->curlform_copycontents["price"] = price;
  }

  void ModHandler::setStock(int stock)
  {
    this->curlform_copycontents["stock"] = stock;
  }

  void ModHandler::setDescription(string description)
  {
    this->curlform_copycontents["description"] = description;
  }

  void ModHandler::setMetadata(string metadata)
  {
    this->curlform_copycontents["metadata"] = metadata;
  }

  void ModHandler::setNameid(string nameid)
  {
    this->curlform_copycontents["nameid"] = nameid;
  }

  void ModHandler::setModfile(int modfile)
  {
    this->curlform_copycontents["modfile"] = modfile;
  }
}
