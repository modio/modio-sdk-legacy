#include "ModworksSDK.h"

#ifdef _WIN32
#define WINDOWS
#endif
#ifdef _WIN64
#define WINDOWS
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

int files_downloaded = 0;
int files_to_download = 5;
bool email_request_finished = false;
bool email_exchange_finished = false;

void onEmailRequest(int response_code)
{
  if(response_code == 200)
  {
    cout<<"Code sent!"<<endl;
  }else
  {
    cout<<"Error sending code"<<endl;
  }
  email_request_finished = true;
}

void onExchange(int response_code)
{
  if(response_code == 200)
  {
    cout<<"Code exchanged!"<<endl;
  }else
  {
    cout<<"Error exchanging code"<<endl;
  }
  email_exchange_finished = true;
}

void onImageDownloaded(int response_code,  modworks::Mod* mod, string path)
{
  if(response_code == 200)
  {
    cout<<mod->name<<" thumb downloaded at "<<path<<endl;
  }
  files_downloaded++;
}

void onModInstalled(int response_code,  modworks::Mod* mod, string path)
{
  if(response_code == 200)
  {
    cout<<mod->name<<" installed at "<<path<<endl;
  }
  files_downloaded++;
}

void onMediaImagesDownloaded(int response_code, modworks::Mod* mod, vector<string> images)
{
  if(response_code == 200)
  {
    cout<<"Media images downloaded:"<<endl;
    for(int i=0;i<(int)images.size();i++)
      cout<<images[i]<<endl;
  }
  files_downloaded++;
}

void onModsGet(int status, vector<modworks::Mod*> mods)
{
  cout<<"Listing mods"<<endl;
  cout<<"============"<<endl;
  for(int i=0;i<(int)mods.size();i++)
  {
    cout<<mods[i]->name<<endl;
    cout<<"username: "<<mods[i]->member->username<<endl;
  }

  cout<<endl<<endl;

  cout<<"Downloads starting"<<endl;
  cout<<"=================="<<endl;
  for(int i=0;i<(int)mods.size();i++)
  {
    modworks::downloadModLogoThumbnail(mods[i], &onImageDownloaded);
    modworks::downloadModLogoFull(mods[i], &onImageDownloaded);
    modworks::downloadModMediaImagesThumbnail(mods[i], &onMediaImagesDownloaded);
    modworks::downloadModMediaImagesFull(mods[i], &onMediaImagesDownloaded);
    modworks::installMod(mods[i], "mod_directory/"+mods[i]->name,&onModInstalled);
  }
}

void onModAdded(int response_code, modworks::Mod* mod)
{
  cout<<"Response code: "<<response_code<<endl;

  if(response_code == 201)
  {
    cout<<"Mod added!"<<endl;
    cout<<"name: "<<mod->name<<endl;

    modworks::AddModFileHandler* add_mod_file_handler = new modworks::AddModFileHandler();
    add_mod_file_handler->setPath("testdir");
    add_mod_file_handler->setVersion("1.0.1");
    add_mod_file_handler->setChangelog("this was a change this was a change");
    modworks::addModFile(mod, add_mod_file_handler, &onModAdded);
  }
}

int main(void)
{
  modworks::init(/*game_id*/7, /*api_key*/"e91c01b8882f4affeddd56c96111977b"/*, "other_dir"*/);
  modworks::setDebugMode(modworks::verbose);

  if(!modworks::isLoggedIn())
  {
    string email;
    cout<<"Enter your email: "<<endl;
    cin>>email;
    modworks::emailRequest(email,&onEmailRequest);
    while(!email_request_finished);
    string security_code;
    cout<<"Please enter the 5 digit security code: ";
    cin>>security_code;
    cout<<"Sending code"<<endl;
    modworks::emailExchange(security_code,&onExchange);
    while(!email_exchange_finished);
  }


  modworks::AddModHandler* add_mod_handler = new modworks::AddModHandler();
  add_mod_handler->setLogoPath("logo.png");
  add_mod_handler->setName("New sdk add method");
  add_mod_handler->setHomepage("http://www.webpage.com");
  add_mod_handler->setSummary("new sdk method new sdk method new sdk method new sdk method new sdk method new sdk method new sdk method new sdk method new sdk method new sdk method");

  modworks::addMod(add_mod_handler, &onModAdded);


/*
  modworks::Filter* filter = new modworks::Filter;
  modworks::addFilterInField(filter,"id","31");
  modworks::getMods(filter, &onModsGet);
  */

  while(true);

  modworks::shutdown();

  cout<<"Process finished"<<endl;

  return 0;
}
