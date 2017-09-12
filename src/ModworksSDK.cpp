#include "ModworksSDK.h"

namespace modworks
{
  string api_key;
  string access_token = "";
  int game_id;

  map< int,AddModParams* > add_mod_callback;
  map< int,function<void(int)> > email_request_callbacks;
  map< int,EmailExchangeParams* > email_exchange_callbacks;
  map< int,function<void(int, vector<Mod*>)> > get_mods_callbacks;

  map< int, AddFileParams* > add_file_callbacks;
  map< int, DownloadThumbnailParams* > download_thumbnail_callbacks;
  map< int, DownloadModfileParams* > download_modfile_callbacks;

  void init(int game_id, string api_key)
  {

    clearLog();

    initCurl();

    writeLogLine("Initializing SDK", verbose);
    modworks::game_id = game_id;
    modworks::api_key = api_key;
    access_token = "";

    std::ifstream token_file(".modworks/token.json");
    if(token_file.is_open())
    {
      json token_file_json;
      token_file >> token_file_json;
      if(token_file_json.find("access_token") != token_file_json.end())
      {
        access_token = token_file_json["access_token"];
      }
    }

    createDirectory(".modworks");
    createDirectory(".modworks/images");
    createDirectory(".modworks/tmp");
    writeLogLine("SDK Initialized", verbose);
  }

  void onGetMods(int call_number, json response)
  {
    vector<Mod*> mods;

    for(int i=0;i<(int)response["data"].size();i++)
    {
      Mod* mod = new Mod(response["data"][i]);
      mods.push_back(mod);
    }

    get_mods_callbacks[call_number](200,mods);
  }

  void getMods(function< void(int, vector<Mod*>) > callback)
  {
    writeLogLine("getMods call", verbose);
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");
    string url = string("https://api.mod.works/v1/games/") + toString(game_id) + "/mods" + "?shhh=secret";

    int call_number = getCallCount();
    advanceCallCount();

    get_mods_callbacks[call_number] = callback;

    std::thread get_mods_thread(get, call_number, url, headers, &onGetMods);
    get_mods_thread.detach();
    writeLogLine("getJson thread detached", verbose);
  }

  void onEmailRequested(int call_number, json response)
  {
    writeLogLine("onEmailRequested call", verbose);
    int result_code = response["code"];
    email_request_callbacks[call_number](result_code);
    email_request_callbacks.erase(call_number);
    writeLogLine("onEmailRequested finished", verbose);
  }

  void emailRequest(string email, function< void(int response) > callback)
  {
    writeLogLine("emailRequest call", verbose);
    map<string, string> data;
    data["api_key"] = api_key;
    data["email"] = email;

    int call_number = getCallCount();
    advanceCallCount();

    email_request_callbacks[call_number] = callback;

    std::thread email_request_thread(post, call_number, "https://api.mod.works/oauth/emailrequest?shhh=secret", data, &onEmailRequested);
    email_request_thread.detach();

    writeLogLine("post detached", verbose);
  }

  void onEmailExchanged(int call_number, json response)
  {
    writeLogLine("onEmailExchanged call", verbose);
    access_token = response["access_token"];

    json token_json;
    token_json["access_token"] = response["access_token"];
    std::ofstream out(".modworks/token.json");
    out<<setw(4)<<token_json<<endl;
    out.close();

    int result_code = response["code"];
    email_exchange_callbacks[call_number]->callback(result_code);
    email_exchange_callbacks.erase(call_number);
    writeLogLine("onEmailExchanged finished", verbose);
  }

  void emailExchange(string security_code, function< void(int) > callback)
  {
    writeLogLine("emailExchange call", verbose);
    map<string, string> data;
    data["api_key"] = api_key;
    data["security_code"] = security_code;

    int call_number = getCallCount();
    advanceCallCount();

    email_exchange_callbacks[call_number] = new EmailExchangeParams;
    email_exchange_callbacks[call_number]->callback = callback;

    std::thread email_exchage_thread(post, call_number, "https://api.mod.works/oauth/emailexchange?shhh=secret",data, &onEmailExchanged);
    email_exchage_thread.detach();

    writeLogLine("post detached", verbose);
  }

  void onModAdded(int call_number, json response)
  {
    Mod* mod = new Mod(response);
    addFile(mod, add_mod_callback[call_number]->directory_path,
                  add_mod_callback[call_number]->version,
                  add_mod_callback[call_number]->changelog,
                  add_mod_callback[call_number]->callback);
    add_mod_callback.erase(call_number);
  }

  void addMod(string name, string homepage, string summary, string logo_path,
                    string directory_path, string version, string changelog,
                    function<void(int, Mod*)> callback)
  {
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

    add_mod_callback[call_number] = new AddModParams;
    add_mod_callback[call_number]->directory_path = directory_path;
    add_mod_callback[call_number]->version = version;
    add_mod_callback[call_number]->changelog = changelog;
    add_mod_callback[call_number]->callback = callback;

    string url = "https://api.mod.works/v1/games/" + toString(game_id) + "/mods";

    std::thread add_mod_thread(modworks::postForm, call_number, url, headers, curlform_copycontents, curlform_files, &onModAdded);
    add_mod_thread.detach();
  }



  void onFileAdded(int call_number, json response)
  {
    add_file_callbacks[call_number]->callback(200,add_file_callbacks[call_number]->mod);
    add_file_callbacks.erase(call_number);
  }


  void addFile(Mod *mod, string directory_path, string version, string changelog, function<void(int, Mod*)> callback)
  {
    modworks::compress(directory_path,".modworks/tmp/modfile.zip");
    vector<string> headers;
    headers.push_back("Authorization: Bearer turupawn");
    map<string, string> curlform_copycontents;
    curlform_copycontents["version"]=version;
    curlform_copycontents["changelog"]=changelog;
    map<string, string> curlform_files;
    curlform_files["filedata"]=".modworks/tmp/modfile.zip";
    string url = string("https://api.mod.works/v1/games/") + toString(7) + "/mods/" + toString(mod->id) + "/files";

    int call_number = getCallCount();
    advanceCallCount();

    add_file_callbacks[call_number] = new AddFileParams;
    add_file_callbacks[call_number]->mod = mod;
    add_file_callbacks[call_number]->callback = callback;

    std::thread add_file_thread(modworks::postForm, call_number, url, headers, curlform_copycontents, curlform_files, &onFileAdded);
    add_file_thread.detach();
  }


  void onThumbnailDownloaded(int call_number, int status, string url, string path)
  {
    download_thumbnail_callbacks[call_number]->callback(status, download_thumbnail_callbacks[call_number]->mod, path);
  }

  void downloadLogoThumbnail(Mod *mod, function< void(int, Mod*, string) > callback)
  {
    writeLogLine("Mod::downloadLogoThumbnail call", verbose);
    string file_path = string(".modworks/images/") + toString(mod->game) + "_" + toString(mod->id) + "_thumb.png";

    int call_number = getCallCount();
    advanceCallCount();

    download_thumbnail_callbacks[call_number] = new DownloadThumbnailParams;
    download_thumbnail_callbacks[call_number]->mod = mod;
    download_thumbnail_callbacks[call_number]->callback = callback;

    //std::thread download_thumbnail_thread(download, call_number, mod->logo_thumbnail_url, file_path, &onThumbnailDownloaded);
    std::thread download_thumbnail_thread(static_cast<void(*)(int call_number, string url, string path, function< void(int, int, string, string) > callback)>(&download), call_number, mod->logo_thumbnail_url, file_path, &onThumbnailDownloaded);

    download_thumbnail_thread.detach();
    writeLogLine("downloadModFile detached", verbose);
  }

  void onModfileDownloaded(int call_number, int status, string url, string path)
  {
    string destintation_path = download_modfile_callbacks[call_number]->destination_path;
    createDirectory(destintation_path);
    extract(path, destintation_path);
    download_modfile_callbacks[call_number]->callback(status, download_modfile_callbacks[call_number]->mod, path);
  }

  void download(Mod *mod, string destination_path, function< void(int, Mod*, string) > callback)
  {
    writeLogLine("Mod::download call", verbose);
    string file_path = string(".modworks/tmp/") + toString(mod->game) + "_" + toString(mod->id) + "_modfile.zip";

    int call_number = getCallCount();
    advanceCallCount();

    download_modfile_callbacks[call_number] = new DownloadModfileParams;
    download_modfile_callbacks[call_number]->mod = mod;
    download_modfile_callbacks[call_number]->destination_path = destination_path;
    download_modfile_callbacks[call_number]->callback = callback;

    std::thread download_thread(static_cast<void(*)(int call_number, string url, string path, function< void(int, int, string, string) > callback)>(&download), call_number, mod->download_url + "?shhh=secret", file_path, &onModfileDownloaded);
    download_thread.detach();

    writeLogLine("downloadRedirect detached", verbose);
  }

  bool isLoggedIn()
  {
    return access_token!="";
  }

  void logout()
  {
    access_token = "";

    json empty_json;
    std::ofstream out(".modworks/token.json");
    out<<setw(4)<<empty_json<<endl;
    out.close();
  }
}
