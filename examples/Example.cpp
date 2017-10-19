#include "ModIOSDK.h"
#include "Filter.h"

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

void onModEdited(int response_code, string message, ModioMod* mod)
{
  cout<<"Response code: "<<response_code<<endl;

  if(response_code == 201)
  {
    cout<<"Mod edited!"<<endl;
  }
}

void onModDeleted(int response_code, string message, ModioMod* mod)
{
  cout<<"Response code: "<<response_code<<endl;

  if(response_code == 204)
  {
    cout<<"Mod deleted!"<<endl;
  }
}

void onEmailRequest(int response_code, char* message)
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

void onExchange(int response_code, char* message)
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

void onImageDownloaded(int response_code, string message, ModioMod* mod, string path)
{
  if(response_code == 200)
  {
    cout<<mod->name<<" thumb downloaded at "<<path<<endl;
  }
  files_downloaded++;
}

void onModInstalled(int response_code, string message, ModioMod* mod, string path)
{
  if(response_code == 200)
  {
    cout<<mod->name<<" installed at "<<path<<endl;
  }
  files_downloaded++;
}

void onMediaImagesDownloaded(int response_code, string message, ModioMod* mod, vector<string> images)
{
  if(response_code == 200)
  {
    cout<<"Media images downloaded:"<<endl;
    for(int i=0;i<(int)images.size();i++)
      cout<<images[i]<<endl;
  }
  files_downloaded++;
}

void onModfileAdded(int response_code, string message, ModioMod* mod)
{
  cout<<"Response: "<<response_code<<endl;
}

void onModfileEdited(int response_code, string message, ModioModfile* modfile)
{
  cout<<"Response: "<<response_code<<endl;
}

void onTagsGet(int response_code, string message, ModioMod* mod, vector<string> tags)
{
  cout<<"Response: "<<response_code<<endl;
  cout<<"Message: "<<message<<endl;

  cout<<"Listing tags:"<<endl;
  cout<<"============="<<endl;
  for(int i=0; i<(int)tags.size();i++)
  {
    cout<<tags[i]<<endl;
  }
}

void onTagsAdded(int response_code, string message, ModioMod* mod)
{
  cout<<"Response: "<<response_code<<endl;
  cout<<"Message: "<<message<<endl;
}

void onModsGet(ModioResponse* response, ModioMod* mods, int mods_size)
{
  cout<<"Response: "<<response->code<<endl;
  cout<<"Listing mods"<<endl;
  cout<<"============"<<endl;

/*
  modio::ModfileHandler* add_mod_file_handler = new modio::ModfileHandler();
  add_mod_file_handler->setPath("moddir");
  add_mod_file_handler->setVersion("v1.1.1");
  add_mod_file_handler->setChangelog("This is a change log, this is a changelog , this is a changelog , this is a changelog , this is a changelog , this is a changelog, this is a changelog , this is a changelog , this is a changelog");

  addModfile(mods[0], add_mod_file_handler, &onModfileAdded);
*/

/*
  cout<<"Version: "<<mods[0]->modfile->version<<endl;
  cout<<"Changelog: "<<mods[0]->modfile->changelog<<endl;
  modio::ModfileHandler* edit_mod_file_handler = new modio::ModfileHandler();
  edit_mod_file_handler->setVersion("v1.1.2");
  edit_mod_file_handler->setChangelog("Changed! This is a change log, this is a changelog , this is a changelog , this is a changelog , this is a changelog , this is a changelog, this is a changelog , this is a changelog , this is a changelog");
  editModfile(mods[0]->modfile, edit_mod_file_handler, &onModfileEdited);
*/

  for(int i=0;i<(int)mods_size;i++)
  {
    //vector<string> tags;
    //tags.push_back("Easy");
    //tags.push_back("Medium");
    cout<<mods[i].name<<endl;
    //modio::getTags(mods[0], &onTagsGet);
  }

  cout<<endl<<endl;

/*
  cout<<"Downloads starting"<<endl;
  cout<<"=================="<<endl;
  for(int i=0;i<(int)mods.size();i++)
  {
    modio::downloadModLogoThumbnail(mods[i], &onImageDownloaded);
    modio::downloadModLogoFull(mods[i], &onImageDownloaded);
    modio::downloadModMediaImagesThumbnail(mods[i], &onMediaImagesDownloaded);
    modio::downloadModMediaImagesFull(mods[i], &onMediaImagesDownloaded);
    modio::installMod(mods[i], "mod_directory/"+mods[i]->name,&onModInstalled);
  }
*/
}

void onModAdded(int response_code, char* message, ModioMod* mod)
{
  cout<<"Response code: "<<response_code<<endl;
  cout<<"Message: "<<message<<endl;

  if(response_code == 201)
  {
    cout<<"Mod added!"<<endl;
    cout<<"name: "<<mod->name<<endl;

/*
    modio::ModfileHandler* modfile_handler = new modio::ModfileHandler();
    modfile_handler->setPath("testdir");
    modfile_handler->setVersion("1.0.1");
    modfile_handler->setChangelog("this was a change this was a change");
    modio::addModfile(mod, modfile_handler, &onModAdded);
*/
  }
}

int main(void)
{
  modioInit(/*game_id*/7, /*api_key*/(char*)"e91c01b8882f4affeddd56c96111977b"/*, "other_dir"*/);
  //modioSetDebugMode(modio::verbose);

  if(!modioIsLoggedIn())
  {
    string email;
    cout<<"Enter your email: "<<endl;
    cin>>email;
    modioEmailRequest((char*)email.c_str(),&onEmailRequest);
    while(!email_request_finished);
    string security_code;
    cout<<"Please enter the 5 digit security code: ";
    cin>>security_code;
    cout<<"Sending code"<<endl;
    modioEmailExchange((char*)security_code.c_str(),&onExchange);
    while(!email_exchange_finished);
  }

/*
  ModHandler* add_mod_handler = new ModHandler;
  setLogoPath(add_mod_handler, "logo.png");
  setName(add_mod_handler, "New sdk add method");
  setHomepage(add_mod_handler, "http://www.webpage.com");
  setSummary(add_mod_handler, "new sdk method new sdk method new sdk method new sdk method new sdk method new sdk method new sdk method new sdk method new sdk method new sdk method");
  addTag(add_mod_handler, "Easy");
  addTag(add_mod_handler, "Medium");

  addMod(add_mod_handler, &onModAdded);
*/


  ModioFilter* filter = new ModioFilter;
  modioInitFilter(filter);
  modioSetFilterCursor(filter,29);
  modioSetFilterLimit(filter,4);
  //modioAddFilterInField(filter,(char*)"id",(char*)"24");
  modioGetMods(filter, &onModsGet);


  while(true);

  modioShutdown();

  cout<<"Process finished"<<endl;

  return 0;
}
