#include "c/creators/ModioModCreator.h"

extern "C"
{
  void modioInitModCreator(ModioModCreator* mod_creator)
  {
    mod_creator->visible = NULL;
    mod_creator->maturity_option = NULL;
    mod_creator->logo = NULL;
    mod_creator->name = NULL;
    mod_creator->name_id = NULL;
    mod_creator->summary = NULL;
    mod_creator->description = NULL;
    mod_creator->homepage_url = NULL;
    mod_creator->metadata_blob = NULL;
    mod_creator->tags = NULL;
  }

  void modioSetModCreatorVisible(ModioModCreator* mod_creator, u32 visible)
  {
    if(mod_creator->visible)
      delete[] mod_creator->visible;

    mod_creator->visible = new char[modio::toString(visible).size() + 1];
    strcpy(mod_creator->visible, modio::toString(visible).c_str());
  }

  void modioSetModCreatorMaturityOption(ModioModCreator* mod_creator, u32 maturity_option)
  {
    if(mod_creator->maturity_option)
      delete[] mod_creator->maturity_option;

    mod_creator->maturity_option = new char[modio::toString(maturity_option).size() + 1];
    strcpy(mod_creator->maturity_option, modio::toString(maturity_option).c_str());
  }

  void modioSetModCreatorLogoPath(ModioModCreator* mod_creator, char const* logo_path)
  {
    if(mod_creator->logo)
      delete[] mod_creator->logo;

    mod_creator->logo = new char[strlen(logo_path) + 1];
    strcpy(mod_creator->logo, logo_path);
  }

  void modioSetModCreatorName(ModioModCreator* mod_creator, char const* name)
  {
    if(mod_creator->name)
      delete[] mod_creator->name;

    mod_creator->name = new char[strlen(name) + 1];
    strcpy(mod_creator->name, name);
  }

  void modioSetModCreatorNameid(ModioModCreator* mod_creator, char const* name_id)
  {
    if(mod_creator->name_id)
    delete[] mod_creator->name_id;

    mod_creator->name_id = new char[strlen(name_id) + 1];
    strcpy(mod_creator->name_id, name_id);
  }

  void modioSetModCreatorSummary(ModioModCreator* mod_creator, char const* summary)
  {
    if(mod_creator->summary)
    delete[] mod_creator->summary;

    mod_creator->summary = new char[strlen(summary) + 1];
    strcpy(mod_creator->summary, summary);
  }

  void modioSetModCreatorDescription(ModioModCreator* mod_creator, char const* description)
  {
    if(mod_creator->description)
    delete[] mod_creator->description;

    mod_creator->description = new char[strlen(description) + 1];
    strcpy(mod_creator->description, description);
  }

  void modioSetModCreatorHomepageURL(ModioModCreator* mod_creator, char const* homepage_url)
  {
    if(mod_creator->homepage_url)
      delete[] mod_creator->homepage_url;

    mod_creator->homepage_url = new char[strlen(homepage_url) + 1];
    strcpy(mod_creator->homepage_url, homepage_url);
  }

  void modioSetModCreatorMetadataBlob(ModioModCreator* mod_creator, char const* metadata_blob)
  {
    if(mod_creator->metadata_blob)
      delete[] mod_creator->metadata_blob;

    mod_creator->metadata_blob = new char[strlen(metadata_blob) + 1];
    strcpy(mod_creator->metadata_blob, metadata_blob);
  }

  void modioAddModCreatorTag(ModioModCreator* mod_creator, char const* tag)
  {
    ModioListNode* new_tag = new ModioListNode;
    modioInitNode(new_tag);
    new_tag->value = new char[strlen(tag) + 1];
    strcpy(new_tag->value, tag);

    if(!mod_creator->tags)
    {
      mod_creator->tags = new_tag;
    }else
    {
      ModioListNode* last_tag = mod_creator->tags;
      while(last_tag->next)
      {
        last_tag = last_tag->next;
      }
      last_tag->next = new_tag;
    }
  }

  void modioFreeModCreator(ModioModCreator* mod_creator)
  {
    if(mod_creator->visible)
      delete[] mod_creator->visible;
    if(mod_creator->maturity_option)
      delete[] mod_creator->maturity_option;
    if(mod_creator->logo)
      delete[] mod_creator->logo;
    if(mod_creator->name)
      delete[] mod_creator->name;
    if(mod_creator->homepage_url)
      delete[] mod_creator->homepage_url;
    if(mod_creator->summary)
      delete[] mod_creator->summary;
    if(mod_creator->description)
      delete[] mod_creator->description;
    if(mod_creator->metadata_blob)
      delete[] mod_creator->metadata_blob;
    if(mod_creator->name_id)
      delete[] mod_creator->name_id;

    if(mod_creator->tags)
      modioFreeNodeList(mod_creator->tags);
  }
}

namespace modio
{
  std::map<std::string, std::string> getModCreatorCurlFormFilesParams(ModioModCreator* mod_creator)
  {
    std::map<std::string, std::string> result;

    if(mod_creator->logo)
      result.insert(std::pair<std::string,std::string>("logo",mod_creator->logo));

    return result;
  }

  std::multimap<std::string, std::string> getModCreatorCurlFormCopyContentsParams(ModioModCreator* mod_creator)
  {
    std::multimap<std::string, std::string> result;

    if(mod_creator->visible)
      result.insert(std::pair<std::string,std::string>("visible",mod_creator->visible));

    if(mod_creator->maturity_option)
      result.insert(std::pair<std::string,std::string>("maturity_option",mod_creator->maturity_option));

    if(mod_creator->name)
      result.insert(std::pair<std::string,std::string>("name",mod_creator->name));

    if(mod_creator->name_id)
      result.insert(std::pair<std::string,std::string>("name_id",mod_creator->name_id));

    if(mod_creator->summary)
      result.insert(std::pair<std::string,std::string>("summary",mod_creator->summary));

    if(mod_creator->description)
      result.insert(std::pair<std::string,std::string>("description",mod_creator->description));

    if(mod_creator->homepage_url)
      result.insert(std::pair<std::string,std::string>("homepage_url",mod_creator->homepage_url));

    if(mod_creator->metadata_blob)
      result.insert(std::pair<std::string,std::string>("metadata_blob",mod_creator->metadata_blob));

    if(mod_creator->tags)
    {
      ModioListNode* current_tag = mod_creator->tags;
      while(current_tag)
      {
        result.insert(std::pair<std::string,std::string>("tags[]",current_tag->value));
        current_tag = current_tag->next;
      }
    }

    return result;
  }
}
