#include "ModworksSDK.h"

int files_downloaded = 0;
int files_to_download = 50;
bool email_request_finished = false;
bool email_exchange_finished = false;

void onModAdded(int result, modworks::Mod* mod)
{
  if(result == 200)
  {
    cout<<"Mod added with id: "<<mod->id<<endl;
  }
}

void onEmailRequest(int result)
{
  if(result == 200)
  {
    cout<<"Code sent!"<<endl;
  }else
  {
    cout<<"Error sending code"<<endl;
  }
  email_request_finished = true;
}

void onExchange(int result)
{
  if(result == 200)
  {
    cout<<"Code exchanged!"<<endl;
  }else
  {
    cout<<"Error exchanging code"<<endl;
  }
  email_exchange_finished = true;
}

void onThumbnailDownloaded(int result,  modworks::Mod* mod, string path)
{
  if(result == 200)
  {
    cout<<mod->name<<" download thumb successful at "<<path<<endl;
  }
  files_downloaded++;
}

void onModInstalled(int result,  modworks::Mod* mod, string path)
{
  if(result == 200)
  {
    cout<<mod->name<<" download file successful at "<<path<<endl;
  }
  files_downloaded++;
}

void onModsGet(int status, vector<modworks::Mod*> mods)
{
  cout<<"Listing mods:"<<endl;
  for(int i=0;i<(int)mods.size();i++)
  {
    cout<<mods[i]->name<<endl;
    modworks::downloadLogoThumbnail(mods[i], &onThumbnailDownloaded);
    modworks::download(mods[i], "mod_directory/"+mods[i]->name,&onModInstalled);
  }
}

void printProgress()
{
  while(files_downloaded<files_to_download)
  {
    cout<<modworks::getCurrentDownloadInfo().url<<endl;
    cout<<modworks::getCurrentDownloadInfo().download_progress
      <<"/"<<modworks::getCurrentDownloadInfo().download_total<<endl;
    sleep(1);
  }
}

int main(void)
{
  modworks::init(/*game_id*/7, /*api_key*/"e91c01b8882f4affeddd56c96111977b"/*, "other_dir"*/);
  modworks::setDebugMode(modworks::verbose);

/*
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
*/

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
  //modworks::setFilterLimit(filter,3);
  modworks::getMods(filter, &onModsGet);

  std::thread print_progress_thread(printProgress);
  print_progress_thread.detach();

  int x;
  cin>>x;

  modworks::shutdown();

  return 0;
}
