#include "ModworksSDK.h"

int files_downloaded = 0;
int files_to_download = 4;
bool email_request_finished = false;
modworks::SDK* mworks;

void onEmailRequest(int result)
{
  if(result == 1)
  {
    cout<<"Code sent!"<<endl;
  }else
  {
    cout<<"Error sending code"<<endl;
  }
  email_request_finished = true;
}

void onThumbnailDownloaded(int result,  modworks::Mod* mod, string path)
{
  if(result == 1)
  {
    cout<<mod->name<<" download thumb successful at "<<path<<endl;
  }
  files_downloaded++;
}

void onModInstalled(int result,  modworks::Mod* mod, string path)
{
  if(result == 1)
  {
    cout<<mod->name<<" download file successful at "<<path<<endl;
  }
  files_downloaded++;
}

void onModsGet(vector<modworks::Mod*> mods)
{
  cout<<endl<<"Listing mods:"<<endl;
  for(int i=0;i<(int)mods.size();i++)
  {
    cout<<mods[i]->name<<endl;
    cout<<mods[i]->summary<<endl;
    mods[i]->downloadLogoThumbnail(&onThumbnailDownloaded);
    mods[i]->download("mod_directory",&onModInstalled);
  }
}


int main(void)
{
  //modworks::compress("dir/path","out.zip");

/*
  vector<string> headers;
  headers.push_back("Authorization: Bearer turupawn");
  map<string, string> curlform_copycontents;
  curlform_copycontents["name"]="testmod111";
  curlform_copycontents["homepage"]="http://www.moddb.com/";
  curlform_copycontents["summary"]="test test test test test test test test test test test test test test test";
  map<string, string> curlform_files;
  curlform_files["logo"]="/home/turupawn/delet/test.png";
  modworks::postForm("https://api.mod.works/v1/games/7/mods", headers, curlform_copycontents, curlform_files);
  /**/

  mworks = new modworks::SDK(/*game_id*/7, /*api_key*/"e91c01b8882f4affeddd56c96111977b");
  mworks->emailRequest("ahmed.hn.43@gmail.com",&onEmailRequest);
  while(!email_request_finished);

  //mworks->getMods(&onModsGet);
  //while(files_downloaded<files_to_download);

  return 0;
}
