#include "extern_c/handlers/ModioModHandler.h"

extern "C"
{
  void modioInitModHandler(ModioModHandler* mod_handler)
  {
    mod_handler->logo = NULL;
    mod_handler->name = NULL;
    mod_handler->homepage = NULL;
    mod_handler->summary = NULL;
    mod_handler->description = NULL;
    mod_handler->metadata_blob = NULL;
    mod_handler->name_id = NULL;
    mod_handler->modfile = NULL;
    mod_handler->tags = NULL;
  }

  void modioSetLogoPath(ModioModHandler* mod_handler, char* logo_path)
  {
    if(mod_handler->logo)
      delete[] mod_handler->logo;

    mod_handler->logo = new char[strlen(logo_path) + 1];
    strcpy(mod_handler->logo, logo_path);
  }

  void modioSetName(ModioModHandler* mod_handler, char* name)
  {
    if(mod_handler->name)
      delete[] mod_handler->name;

    mod_handler->name = new char[strlen(name) + 1];
    strcpy(mod_handler->name, name);
  }

  void modioSetHomepage(ModioModHandler* mod_handler, char* homepage)
  {
    if(mod_handler->homepage)
      delete[] mod_handler->homepage;

    mod_handler->homepage = new char[strlen(homepage) + 1];
    strcpy(mod_handler->homepage, homepage);
  }

  void modioSetSummary(ModioModHandler* mod_handler, char* summary)
  {
    if(mod_handler->summary)
      delete[] mod_handler->summary;

    mod_handler->summary = new char[strlen(summary) + 1];
    strcpy(mod_handler->summary, summary);
  }

  void modioSetDescription(ModioModHandler* mod_handler, char* description)
  {
    if(mod_handler->description)
      delete[] mod_handler->description;

    mod_handler->description = new char[strlen(description) + 1];
    strcpy(mod_handler->description, description);
  }

  void modioSetMetadataBlob(ModioModHandler* mod_handler, char* metadata_blob)
  {
    if(mod_handler->metadata_blob)
      delete[] mod_handler->metadata_blob;

    mod_handler->metadata_blob = new char[strlen(metadata_blob) + 1];
    strcpy(mod_handler->metadata_blob, metadata_blob);
  }

  void modioSetNameid(ModioModHandler* mod_handler, char* name_id)
  {
    if(mod_handler->name_id)
      delete[] mod_handler->name_id;

    mod_handler->name_id = new char[strlen(name_id) + 1];
    strcpy(mod_handler->name_id, name_id);
  }

  void modioSetModfile(ModioModHandler* mod_handler, u32 modfile)
  {
    if(mod_handler->modfile)
      delete[] mod_handler->modfile;

    mod_handler->modfile = new char[modio::toString(modfile).size() + 1];
    strcpy(mod_handler->modfile, modio::toString(modfile).c_str());
  }

  void modioAddTag(ModioModHandler* mod_handler, char* tag)
  {
    ModioListNode* new_tag = new ModioListNode;
    modioInitNode(new_tag);
    new_tag->value = new char[strlen(tag) + 1];
    strcpy(new_tag->value, tag);

    if(!mod_handler->tags)
    {
      mod_handler->tags = new_tag;
    }else
    {
      ModioListNode* last_tag = mod_handler->tags;
      while(last_tag->next)
      {
        last_tag = last_tag->next;
      }
      last_tag->next = new_tag;
    }
  }

  void modioFreeModHandler(ModioModHandler* mod_handler)
  {
    delete mod_handler->logo;
    delete mod_handler->name;
    delete mod_handler->homepage;
    delete mod_handler->summary;
    delete mod_handler->description;
    delete mod_handler->metadata_blob;
    delete mod_handler->name_id;
    delete mod_handler->modfile;
    delete mod_handler->tags;
  }
}

namespace modio
{
  std::map<std::string, std::string> getModfileCurlFormFilesParams(ModioModHandler* mod_handler)
  {
    std::map<std::string, std::string> result;

    if(mod_handler->logo)
      result.insert(std::pair<std::string,std::string>("logo",mod_handler->logo));

    return result;
  }

  std::multimap<std::string, std::string> getModfileCurlFormCopyContentsParams(ModioModHandler* mod_handler)
  {
    std::multimap<std::string, std::string> result;

    if(mod_handler->name)
      result.insert(std::pair<std::string,std::string>("name",mod_handler->name));

    if(mod_handler->homepage)
      result.insert(std::pair<std::string,std::string>("homepage",mod_handler->homepage));

    if(mod_handler->summary)
      result.insert(std::pair<std::string,std::string>("summary",mod_handler->summary));

    if(mod_handler->description)
      result.insert(std::pair<std::string,std::string>("description",mod_handler->description));

    if(mod_handler->name_id)
      result.insert(std::pair<std::string,std::string>("name_id",mod_handler->name_id));

    if(mod_handler->modfile)
      result.insert(std::pair<std::string,std::string>("modfile",mod_handler->modfile));

    if(mod_handler->metadata_blob)
      result.insert(std::pair<std::string,std::string>("metadata_blob",mod_handler->metadata_blob));

    if(mod_handler->tags)
    {
      ModioListNode* current_tag = mod_handler->tags;
      while(current_tag)
      {
        result.insert(std::pair<std::string,std::string>("tags[]",current_tag->value));
        current_tag = current_tag->next;
      }
    }

    return result;
  }
}
