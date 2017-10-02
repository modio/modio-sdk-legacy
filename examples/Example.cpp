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
int files_to_download = 50;
bool email_request_finished = false;
bool email_exchange_finished = false;

void onModAdded(int response_code, modworks::Mod* mod)
{
  if(response_code == 200)
  {
    cout<<"Mod added with id: "<<mod->id<<endl;
  }
}

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

void onThumbnailDownloaded(int response_code,  modworks::Mod* mod, string path)
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
}

void onModsGet(int status, vector<modworks::Mod*> mods)
{
  cout<<"Listing mods"<<endl;
  cout<<"============"<<endl;
  for(int i=0;i<(int)mods.size();i++)
  {
    cout<<mods[i]->name<<endl;
  }

  cout<<endl<<endl;

  cout<<"Downloads starting"<<endl;
  cout<<"=================="<<endl;
  for(int i=0;i<(int)mods.size();i++)
  {
    modworks::downloadModLogoThumbnail(mods[i], &onThumbnailDownloaded);
    modworks::downloadModLogoFull(mods[i], &onThumbnailDownloaded);
    modworks::downloadModMediaImagesThumbnail(mods[i], &onMediaImagesDownloaded);
    modworks::downloadModMediaImagesFull(mods[i], &onMediaImagesDownloaded);
    modworks::installMod(mods[i], "mod_directory/"+mods[i]->name,&onModInstalled);
  }
}

void printProgress()
{
  while(files_downloaded<files_to_download)
  {
    if(modworks::getCurrentDownloadInfo().url != "")
    {
      double percentage = 0;
      if(modworks::getCurrentDownloadInfo().download_progress != 0 && modworks::getCurrentDownloadInfo().download_total != 0)
        percentage = 100.0 * modworks::getCurrentDownloadInfo().download_progress / modworks::getCurrentDownloadInfo().download_total;
      cout<<percentage<<"%"<<endl;
      sleep(1);
    }
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

/*
  mworks->addMod( "test22",//Mod params
                  "http://hello.com",
                  "test test test test test test test test test test test test test test test",
                  "logo.png",
                  "dir/moddir",//File params
                  "0.0.1",
                  "This is a changelog text",
                  &onModAdded);//Callback
*/

  modworks::Filter* filter = new modworks::Filter;
  modworks::addFilterInField(filter,"id","31");
  modworks::getMods(filter, &onModsGet);

  while(true);

/*
  int x;
  cin>>x;

  modworks::pauseCurrentDownload();

  cin>>x;

  cout<<"Process finished!"<<endl;
*/
  modworks::shutdown();

  return 0;
}
