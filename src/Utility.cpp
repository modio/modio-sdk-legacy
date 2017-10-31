#include "Utility.h"

extern "C"
{
  void modioInitNode(Node* node)
  {
    node->value = NULL;
    node->next = NULL;
  }

  void modioFreeNodeList(Node* node)
  {
    if(node->value)
      delete node->value;

    if(node->next)
      modioFreeNodeList(node->next);
  }
}

namespace modio
{
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

  string toString(double number)
  {
    ostringstream string_stream;
    string_stream << number;
    string return_value = string_stream.str();
    return return_value;
  }

  void createDirectory(string directory)
  {
    #ifdef LINUX
      mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #endif

    #ifdef OSX
      mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #endif

    #ifdef WINDOWS
      CreateDirectory(directory.c_str() ,NULL);
    #endif
  }

  void clearLog()
  {
    ofstream log_file(getModIODirectory() + "log");
    log_file.close();
  }

  void writeLogLine(string text, unsigned int debug_level)
  {
    // NOTE(@jackson): Lower value is higher severity (error == 0)
    if(DEBUG_LEVEL < debug_level)
      return;

    ofstream log_file(getModIODirectory() + "log", ios::app);
    if(debug_level == MODIO_DEBUGLEVEL_ERROR) { log_file<<"Error: "; }
    else if(debug_level == MODIO_DEBUGLEVEL_WARNING) { log_file<<"Warning: "; }
    log_file<<text.c_str()<<"\n";
    log_file.close();
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

  string getModIODirectory()
  {
    // TODO(@turupawn): Can we handle paths passed as C:\ rather than C:/ ?
    //  (re: windows programmers like myself)
    if(ROOT_PATH != "" && ROOT_PATH[ROOT_PATH.size()-1] != '/')
      ROOT_PATH += "/";
    return ROOT_PATH + ".modio/";
  }

  bool hasKey(json json_object, string key)
  {
    return json_object.find(key) != json_object.end() && !json_object[key].is_null();
  }

  void removeFile(string filename)
  {
    if(remove(filename.c_str()) != 0)
      writeLogLine("Could not remove " + filename, MODIO_DEBUGLEVEL_ERROR);
    else
      writeLogLine(filename + " removed", MODIO_DEBUGLEVEL_LOG);
  }
}
