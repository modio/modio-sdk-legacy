#include "c/schemas/ModioTerms.h"
#include "Utility.h"                    // for hasKey

static void initString(const nlohmann::json& json, char*& destination, const char* variableName)
{
  destination = nullptr;
  if (modio::hasKey(json, variableName) && json[variableName].is_string())
  {
    const std::string& sourceVariable = json[variableName];
    destination = new char[sourceVariable.size() + 1];
    destination[sourceVariable.size()] = '\0';
    strcpy(destination, sourceVariable.c_str());
  }
}

static void copyString(char*& destination, const std::string& source)
{
  destination = new char[source.size()+1];
  strcpy(destination, source.c_str());
}

static void safeFreeString(char*& string)
{
  if(string)
  {
    delete[] string;
  }
}

static void initBool(const nlohmann::json& json, bool& destination, const char* variableName)
{
  if (modio::hasKey(json, variableName) && json[variableName].is_boolean())
  {
    destination = json[variableName];
  }
}

extern "C"
{
  void modioInitTerms(ModioTerms* terms, const nlohmann::json& terms_json)
  {
    initString(terms_json,terms->plaintext, "plaintext");
    initString(terms_json, terms->html, "html");

    if(modio::hasKey(terms_json, "buttons"))
    {
      const nlohmann::json& buttons_json = terms_json["buttons"];
      if (modio::hasKey(buttons_json, "agree"))
      {
        modioInitButton(&terms->agree, buttons_json["agree"]);
      }

      if (modio::hasKey(buttons_json, "disagree"))
      {
        modioInitButton(&terms->disagree, buttons_json["disagree"]);
      }
    }

    if (modio::hasKey(terms_json, "links"))
    {
      const nlohmann::json& links_json = terms_json["links"];
      if (modio::hasKey(links_json, "manage"))
      {
        modioInitLink(&terms->manage, links_json["manage"]);
      }

      if (modio::hasKey(links_json, "privacy"))
      {
        modioInitLink(&terms->privacy, links_json["privacy"]);
      }
      if (modio::hasKey(links_json, "terms"))
      {
        modioInitLink(&terms->terms, links_json["terms"]);
      }
      if (modio::hasKey(links_json, "website"))
      {
        modioInitLink(&terms->website, links_json["website"]);
      }
    }
  }

  void modioInitTermsCpp(ModioTerms* modio_terms, const modio::Terms* terms)
  {
    modioInitButtonCpp(&modio_terms->agree, &terms->agree);
    modioInitButtonCpp(&modio_terms->disagree, &terms->disagree);

    copyString(modio_terms->html, terms->html);
    copyString(modio_terms->plaintext, terms->plaintext);

    modioInitLinkCpp(&modio_terms->manage, &terms->manage);
    modioInitLinkCpp(&modio_terms->privacy, &terms->privacy);
    modioInitLinkCpp(&modio_terms->terms, &terms->terms);
    modioInitLinkCpp(&modio_terms->website, &terms->website);
  }

  void modioFreeTerms(ModioTerms* terms)
  {
    modioFreeButton(&terms->agree);
    modioFreeButton(&terms->disagree);

    safeFreeString(terms->html);
    safeFreeString(terms->plaintext);

    modioFreeLink(&terms->manage);
    modioFreeLink(&terms->privacy);
    modioFreeLink(&terms->terms);
    modioFreeLink(&terms->website);
  }

  void modioInitButton(ModioButton* button, const nlohmann::json& button_json)
  {
    initString(button_json, button->text, "text");
  }

  void modioInitButtonCpp(ModioButton* modio_button, const modio::Button* button)
  {
    copyString(modio_button->text, button->text);
  }

  void modioFreeButton(ModioButton* button)
  {
    safeFreeString(button->text);
  }

  void modioInitLink(ModioLink* link, const nlohmann::json& link_json)
  {
    initString(link_json, link->text, "text");
    initString(link_json, link->url, "url");
    initBool(link_json, link->required, "required");
  }

  void modioInitLinkCpp(ModioLink* modio_link, const modio::Link* link)
  {
    copyString(modio_link->text, link->text);
    copyString(modio_link->url, link->url);
    modio_link->required = link->required;
  }

  void modioFreeLink(ModioLink* link)
  {
    safeFreeString(link->text);
    safeFreeString(link->url);
  }
}
