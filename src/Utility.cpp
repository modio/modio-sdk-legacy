#include "Utility.h"

namespace modworks
{
  string dataToJsonString(char* data, size_t size)
  {
    int brackets = 0;
    string response;
    for(int i=0; i<(int)size; i++)
    {
      if(data[i]=='{')
        brackets++;

      if(brackets>0)
      {
        response+=data[i];
      }

      if(data[i]=='}')
        brackets--;
    }
    return response;
  }

  string toString(int number)
  {
      if (number == 0)
          return "0";

      if(number < 0)
          return "-"+toString(-number);

      std::string temp="";
      std::string returnvalue="";
      while (number>0)
      {
          temp+=number%10+48;
          number/=10;
      }
      for (int i=0;i<(int)temp.length();i++)
          returnvalue+=temp[temp.length()-i-1];
      return returnvalue;
  }

  void createDirectory(string directory)
  {
    #ifdef LINUX
      mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #endif

    #ifdef WINDOWS
      CreateDirectory(directory.c_str() ,NULL);
    #endif
  }

  void clearLog()
  {
    ofstream log_file(".modworks/log");
    log_file.close();
  }

  bool writeLogLine(string text, DebugMode debug_mode)
  {
    ofstream log_file(".modworks/log", ios::app);
    if(debug_mode == error)
      log_file<<"Error: ";
    log_file<<text.c_str()<<"\n";
    log_file.close();
    return true;
  }

  vector<string> getFilenames(string directory)
  {
    vector<string> filenames;
    struct dirent *ent;
    DIR *dir;

    if(directory[directory.size()-1]!='/')
      directory += '/';

    if ((dir = opendir (directory.c_str())) != NULL)
    {
      while ((ent = readdir (dir)) != NULL)
      {
        DIR* current_dir;
        string current_file_path = directory + ent->d_name;
        if ((current_dir = opendir( current_file_path.c_str() )) != NULL && strcmp(ent->d_name,".") != 0 && strcmp(ent->d_name,"..") != 0)
        {
          vector<string> subdirectories_filenames = getFilenames(directory + ent->d_name);
          for(int i=0;i<(int)subdirectories_filenames.size();i++)
          {
            filenames.push_back(string(ent->d_name) + "/" + subdirectories_filenames[i]);
          }
          closedir(current_dir);
        }else if(strcmp(ent->d_name,".") != 0 && strcmp(ent->d_name,"..") != 0)
        {
          filenames.push_back(ent->d_name);
        }

      }
      closedir (dir);
    }
    return filenames;
  }
}
