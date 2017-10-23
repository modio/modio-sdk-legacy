#include "handlers/ModHandler.h"

extern "C"
{
  void modioSetLogoPath(ModioModHandler* mod_handler, string logo_path)
  {
    mod_handler->curlform_files["logo"] = logo_path;
  }

  void modioSetName(ModioModHandler* mod_handler, string name)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("name",name));
  }

  void modioSetHomepage(ModioModHandler* mod_handler, string homepage)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("homepage",homepage));
  }

  void modioSetSummary(ModioModHandler* mod_handler, string summary)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("summary",summary));
  }

  void modioSetPrice(ModioModHandler* mod_handler, double price)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("price", modio::toString(price)));
  }

  void modioSetStock(ModioModHandler* mod_handler, int stock)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("stock", modio::toString(stock)));
  }

  void modioSetDescription(ModioModHandler* mod_handler, string description)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("description",description));
  }

  void modioSetMetadata(ModioModHandler* mod_handler, string metadata)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("metadata",metadata));
  }

  void modioSetNameid(ModioModHandler* mod_handler, string nameid)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("nameid",nameid));
  }

  void modioSetModfile(ModioModHandler* mod_handler, int modfile)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("modfile", modio::toString(modfile)));
  }

  void modioAddTag(ModioModHandler* mod_handler, string tag)
  {
    mod_handler->curlform_copycontents.insert(pair<string,string>("tags[]",tag));
  }
}
