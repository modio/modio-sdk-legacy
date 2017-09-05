#include "ModworksSDK.h"

namespace modworks
{
  SDK::SDK(int game_id, string api_key)
  {
    clearLog();

    initCurl();

    writeLogLine("Initializing SDK", verbose);
    this->game_id = game_id;
    this->api_key = api_key;
    this->access_token = "";

    createDirectory(".modworks");
    createDirectory(".modworks/images");
    createDirectory(".modworks/tmp");
    writeLogLine("SDK Initialized", verbose);
  }

  void SDK::getMods(function< void(vector<Mod*>) > callback)
  {
    writeLogLine("getMods call", verbose);
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");
    string url = string("https://api.mod.works/v1/games/") + toString(game_id) + "/mods";

    int call_count = getCallCount();
    advanceCallCount();

    std::thread get_json_thread(getJson, url, headers, callback, call_count);
    get_json_thread.detach();
    writeLogLine("getJson thread detached", verbose);
  }

  void SDK::onEmailRequested(int call_number, json response, map<string, string> params)
  {
    writeLogLine("onEmailRequested call", verbose);
    int result_code = response["code"];
    email_request_callbacks[call_number](result_code);
    email_request_callbacks.erase(call_number);
    writeLogLine("onEmailRequested finished", verbose);
  }

  void SDK::emailRequest(string email, function< void(int response) > callback)
  {
    writeLogLine("emailRequest call", verbose);
    map<string, string> data;
    data["api_key"] = api_key;
    data["email"] = email;

    int call_number = getCallCount();
    advanceCallCount();

    email_request_callbacks[call_number] = callback;

    map<string, string> params;

    auto on_email_requested_ptr = std::bind(&SDK::onEmailRequested, *this, placeholders::_1, placeholders::_2, placeholders::_3);
    std::thread email_request_thread(post, call_number, params, "https://api.mod.works/oauth/emailrequest?shhh=secret", data, on_email_requested_ptr);
    email_request_thread.detach();

    writeLogLine("post detached", verbose);
  }

  void SDK::onEmailExchanged(int call_number, json response, map<string, string> params)
  {
    writeLogLine("onEmailExchanged call", verbose);
    this->access_token = response["access_token"];

    json token_json;
    token_json["access_token"] = this->access_token;
    std::ofstream out(".modworks/token.json");
    out<<setw(4)<<token_json<<endl;
    out.close();

    int result_code = response["code"];
    email_exchange_callbacks[call_number](result_code);
    email_exchange_callbacks.erase(call_number);
    writeLogLine("onEmailExchanged finished", verbose);
  }

  void SDK::emailExchange(string security_code, function< void(int) > callback)
  {
    writeLogLine("emailExchange call", verbose);
    map<string, string> data;
    data["api_key"] = api_key;
    data["security_code"] = security_code;

    int call_number = getCallCount();
    advanceCallCount();

    email_exchange_callbacks[call_number] = callback;

    map<string, string> params;

    auto on_email_exchanged_ptr = std::bind(&SDK::onEmailExchanged, *this, placeholders::_1, placeholders::_2, placeholders::_3);
    std::thread email_exchage_thread(post, call_number, params, "https://api.mod.works/oauth/emailexchange?shhh=secret",data, on_email_exchanged_ptr);
    email_exchage_thread.detach();

    writeLogLine("post detached", verbose);
  }

  void SDK::onModAdded(int call_number, json response, map<string, string> params)
  {
    Mod* mod = new Mod(response);
    mod->addFile(params["directory_path"], params["version"], params["changelog"], add_mod_callback[call_number]);
    add_mod_callback.erase(call_number);
  }

  void SDK::addMod(/*Mod params*/string name, string homepage, string summary, string logo_path,
                    /*File params*/string directory_path, string version, string changelog,
                    /*Callback*/function<void(int, Mod*)> callback)
  {
    this->directory_path = directory_path;
    this->version = version;
    this->changelog = changelog;

    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");
    map<string, string> curlform_copycontents;
    curlform_copycontents["name"]=name;
    curlform_copycontents["homepage"]=homepage;
    curlform_copycontents["summary"]=summary;
    map<string, string> curlform_files;
    curlform_files["logo"]=logo_path;

    map<string,string> params;
    params["directory_path"] = directory_path;
    params["version"] = version;
    params["changelog"] = changelog;

    int call_number = getCallCount();
    advanceCallCount();

    add_mod_callback[call_number] = callback;

    string url = "https://api.mod.works/v1/games/" + toString(game_id) + "/mods";
    auto on_mod_added_ptr = std::bind(&SDK::onModAdded, *this, placeholders::_1, placeholders::_2, placeholders::_3);
    std::thread add_mod_thread(modworks::postForm, call_number, params, url, headers, curlform_copycontents, curlform_files, on_mod_added_ptr);
    add_mod_thread.detach();
  }
}
