#include "handlers/ModHandler.h"

namespace modio
{
  void setLogoPath(ModHandler* mod_handler, string logo_path)
  {
    mod_handler->curlform_files["logo"] = logo_path;
  }

  void setName(ModHandler* mod_handler, string name)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("name",name));
  }

  void setHomepage(ModHandler* mod_handler, string homepage)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("homepage",homepage));
  }

  void setSummary(ModHandler* mod_handler, string summary)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("summary",summary));
  }

  void setPrice(ModHandler* mod_handler, double price)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("price",toString(price)));
  }

  void setStock(ModHandler* mod_handler, int stock)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("stock",toString(stock)));
  }

  void setDescription(ModHandler* mod_handler, string description)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("description",description));
  }

  void setMetadata(ModHandler* mod_handler, string metadata)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("metadata",metadata));
  }

  void setNameid(ModHandler* mod_handler, string nameid)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("nameid",nameid));
  }

  void setModfile(ModHandler* mod_handler, int modfile)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("modfile",toString(modfile)));
  }

  void addTag(ModHandler* mod_handler, string tag)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("tags[]",tag));
  }
}
