#include "c++/schemas/Terms.h"
#include "c/ModioC.h"
#include "dependencies/nlohmann/json.hpp"

static void copyString(std::string& destination, const char* source)
{
  if(source)
  {
    destination = source;
  }
}

namespace modio
{
  void Terms::initialize(const ModioTerms& inTerms)
  {
    copyString(plaintext, inTerms.plaintext);
    copyString(html, inTerms.html);

    agree.initialize(inTerms.agree);
    disagree.initialize(inTerms.disagree);

    website.initialize(inTerms.website);
    terms.initialize(inTerms.terms);
    privacy.initialize(inTerms.privacy);
    manage.initialize(inTerms.manage);
  }

  void Link::initialize(const ModioLink& link)
  {
    copyString(text, link.text);
    copyString(url, link.url);
    required = link.required;
  }

  void Button::initialize(const ModioButton& button)
  {
    copyString(text, button.text);
  }



}