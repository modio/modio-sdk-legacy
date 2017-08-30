#ifndef MODWORKS_SDK_H
#define MODWORKS_SDK_H

#include "CurlWrapper.h"
#include "MinizipWrapper.h"
#include "Mod.h"

namespace modworks
{
  class SDK
  {
  public:
    string api_key;
    string access_token;
    int game_id;

    SDK(int game_id, string api_key);
    void getMods(function< void(vector<Mod*>) > callback);
    void onEmailRequested(json response, function< void(int response) > callback);
    void emailRequest(string email, function< void(int response) > callback);
    void onEmailExchanged(json response, function< void(int) > callback);
    void emailExchange(string security_code, function< void(int response) > callback);
  };
}

#endif
