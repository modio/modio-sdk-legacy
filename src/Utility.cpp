#include "Utility.h"

namespace modio
{
  std::string toString(i32 number)
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

  std::string toString(u32 number)
  {
    return toString((i32)number);
  }

  std::string toString(double number)
  {
    return std::to_string(number);
  }

  void createDirectory(std::string directory)
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
    std::ofstream log_file(getModIODirectory() + "log");
    log_file.close();
  }

  void writeLogLine(std::string text, unsigned int debug_level)
  {
    // NOTE(@jackson): Lower value is higher severity (error == 0)
    if(DEBUG_LEVEL < debug_level)
      return;

    std::ofstream log_file(getModIODirectory() + "log", std::ios::app);
    log_file<<"["<<modio::getCurrentTime()<<"] ";
    if(debug_level == MODIO_DEBUGLEVEL_ERROR) { log_file<<"[Error] "; }
    else if(debug_level == MODIO_DEBUGLEVEL_WARNING) { log_file<<"[WARNING] "; }
    else if(debug_level == MODIO_DEBUGLEVEL_LOG) { log_file<<"[LOG] "; }
    log_file<<text.c_str()<<"\n";
    log_file.close();
  }

  std::vector<std::string> getFilenames(std::string directory)
  {
    std::vector<std::string> filenames;
    struct dirent *ent;
    DIR *dir;
    if(directory[directory.size()-1]!='/')
      directory += '/';

    if ((dir = opendir (directory.c_str())) != NULL)
    {
      while ((ent = readdir (dir)) != NULL)
      {
        DIR* current_dir;
        std::string current_file_path = directory + ent->d_name;
        if ((current_dir = opendir( current_file_path.c_str() )) != NULL && strcmp(ent->d_name,".") != 0 && strcmp(ent->d_name,"..") != 0)
        {
          std::vector<std::string> subdirectories_filenames = getFilenames(directory + ent->d_name);
          for(int i=0;i<(int)subdirectories_filenames.size();i++)
          {
            filenames.push_back(std::string(ent->d_name) + "/" + subdirectories_filenames[i]);
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

  std::string getModIODirectory()
  {
    // TODO(@turupawn): Can we handle paths passed as C:\ rather than C:/ ?
    //  (re: windows programmers like myself)
    if(ROOT_PATH != "" && ROOT_PATH[ROOT_PATH.size()-1] != '/')
      ROOT_PATH += "/";
    return ROOT_PATH + ".modio/";
  }

  bool hasKey(json json_object, std::string key)
  {
    return json_object.find(key) != json_object.end() && !json_object[key].is_null();
  }

  void removeFile(std::string filename)
  {
    if(remove(filename.c_str()) != 0)
      writeLogLine("Could not remove " + filename, MODIO_DEBUGLEVEL_ERROR);
    else
      writeLogLine(filename + " removed", MODIO_DEBUGLEVEL_LOG);
  }

  void removeEmptyDirectory(std::string path)
  {


    #ifdef LINUX
      if(remove(path.c_str()))
        writeLogLine(path + " removed", MODIO_DEBUGLEVEL_LOG);
      else
        writeLogLine("Could not remove " + path, MODIO_DEBUGLEVEL_ERROR);
    #endif

    #ifdef OSX
      if(remove(path.c_str()))
        writeLogLine(path + " removed", MODIO_DEBUGLEVEL_LOG);
      else
        writeLogLine("Could not remove " + path, MODIO_DEBUGLEVEL_ERROR);
    #endif

    #ifdef WINDOWS
      if(RemoveDirectory(path.c_str()))
        writeLogLine("File removed " + path, MODIO_DEBUGLEVEL_LOG);
      else
        writeLogLine("Could not remove file " + path, MODIO_DEBUGLEVEL_ERROR);
    #endif
  }

  bool removeDirectory(std::string directory_name)
  {
    DIR *dir;
    struct dirent *entry;
    char path[PATH_MAX];

    if(directory_name[directory_name.size()-1]!='/')
      directory_name += '/';

    dir = opendir(directory_name.c_str());
    if (dir == NULL)
    {
      writeLogLine("Error opendir()", MODIO_DEBUGLEVEL_LOG);
      return false;
    }

    while ((entry = readdir(dir)) != NULL)
    {
      if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
      {
        snprintf(path, (size_t) PATH_MAX, "%s%s", directory_name.c_str(), entry->d_name);
        if(opendir(path) != NULL)
        {
            removeDirectory(path);
        }
        writeLogLine("Deleting: " + std::string(path), MODIO_DEBUGLEVEL_LOG);
        removeFile(path);
      }
    }
    closedir(dir);
    writeLogLine("Deleting: " + directory_name, MODIO_DEBUGLEVEL_LOG);
    removeEmptyDirectory(directory_name);

    return true;
  }

  std::string addSlashIfNeeded(std::string directory_path)
  {
    if(directory_path!= "" && directory_path[directory_path.size()-1] != '/')
      directory_path += "/";

    return directory_path;
  }

  json openJson(std::string file_path)
  {
    std::ifstream ifs(file_path);
    json cache_file_json;
    if(ifs.is_open())
    {
      try
      {
        ifs >> cache_file_json;
      }catch(json::parse_error &e)
      {
        modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
        cache_file_json = {};
      }
    }
    ifs.close();
    return cache_file_json;
  }

  void writeJson(std::string file_path, json json_object)
  {
    std::ofstream ofs(file_path);
    ofs << std::setw(4) << json_object << std::endl;
    ofs.close();
  }

  u32 getCurrentTime()
  {
    return (u32)std::time(nullptr);
  }
}
