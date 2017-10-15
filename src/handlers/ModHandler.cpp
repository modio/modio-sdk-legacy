#include "handlers/ModHandler.h"

namespace modio
{
  void ModHandler::setLogoPath(string logo_path)
  {
    this->curlform_files["logo"] = logo_path;
  }

  void ModHandler::setName(string name)
  {
    this->curlform_copycontents.insert(pair<string,string>("name",name));
  }

  void ModHandler::setHomepage(string homepage)
  {
    this->curlform_copycontents.insert(pair<string,string>("homepage",homepage));
  }

  void ModHandler::setSummary(string summary)
  {
    this->curlform_copycontents.insert(pair<string,string>("summary",summary));
  }

  void ModHandler::setPrice(double price)
  {
    this->curlform_copycontents.insert(pair<string,string>("price",toString(price)));
  }

  void ModHandler::setStock(int stock)
  {
    this->curlform_copycontents.insert(pair<string,string>("stock",toString(stock)));
  }

  void ModHandler::setDescription(string description)
  {
    this->curlform_copycontents.insert(pair<string,string>("description",description));
  }

  void ModHandler::setMetadata(string metadata)
  {
    this->curlform_copycontents.insert(pair<string,string>("metadata",metadata));
  }

  void ModHandler::setNameid(string nameid)
  {
    this->curlform_copycontents.insert(pair<string,string>("nameid",nameid));
  }

  void ModHandler::setModfile(int modfile)
  {
    this->curlform_copycontents.insert(pair<string,string>("modfile",toString(modfile)));
  }

  void ModHandler::addTag(string tag)
  {
    this->curlform_copycontents.insert(pair<string,string>("tags[]",tag));
  }
}
