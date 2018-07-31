#include "Utility.h"

namespace modio
{
//String methods
std::string toString(i32 number)
{
  if (number == 0)
    return "0";

  if (number < 0)
    return "-" + toString(-number);

  std::string temp = "";
  std::string returnvalue = "";
  while (number > 0)
  {
    temp += number % 10 + 48;
    number /= 10;
  }
  for (int i = 0; i < (int)temp.length(); i++)
    returnvalue += temp[temp.length() - i - 1];
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

std::string replaceSubstrings(std::string str, const std::string &from, const std::string &to)
{
  if (from == "")
    return str;

  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos)
  {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
  return str;
}

std::string addSlashIfNeeded(std::string directory_path)
{
  if (directory_path != "" && directory_path[directory_path.size() - 1] != '/')
    directory_path += "/";

  return directory_path;
}

// Log methods

void writeLogLine(std::string text, u32 debug_level)
{
  // NOTE(@jackson): Lower value is higher severity (error == 0)
  if (DEBUG_LEVEL < debug_level)
    return;

  std::ofstream log_file(getModIODirectory() + "log", std::ios::app);
  log_file << "[" << modio::getCurrentTime() << "] ";
  if (debug_level == MODIO_DEBUGLEVEL_ERROR)
  {
    log_file << "[Error] ";
  }
  else if (debug_level == MODIO_DEBUGLEVEL_WARNING)
  {
    log_file << "[WARNING] ";
  }
  else if (debug_level == MODIO_DEBUGLEVEL_LOG)
  {
    log_file << "[LOG] ";
  }
  log_file << text.c_str() << "\n";
  log_file.close();
}

void clearLog()
{
  std::ofstream log_file(getModIODirectory() + "log");
  log_file.close();
}

// Time methods

u32 getCurrentTime()
{
  return (u32)std::time(nullptr);
}

// Json methods

bool hasKey(json json_object, std::string key)
{
  return json_object.find(key) != json_object.end() && !json_object[key].is_null();
}

json toJson(std::string json_str)
{
  if (json_str == "")
    return "{}"_json;

  json response_json;
  try
  {
    response_json = json::parse(json_str);
  }
  catch (json::parse_error &e)
  {
    writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
    response_json = "{}"_json;
  }
  return response_json;
}

json openJson(std::string file_path)
{
  std::ifstream ifs(file_path);
  json cache_file_json;
  if (ifs.is_open())
  {
    try
    {
      ifs >> cache_file_json;
    }
    catch (json::parse_error &e)
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

// Filesystem methods

#ifdef WINDOWS
void writeLastErrorLog(std::string error_function)
{
  //Get the error message, if any.
  DWORD errorMessageID = ::GetLastError();
  if (errorMessageID == 0)
    return; //No error message has been recorded

  if (errorMessageID == 183)
  {
    modio::writeLogLine("The directory already exists.", MODIO_DEBUGLEVEL_LOG);
    return;
  }

  LPSTR messageBuffer = nullptr;
  size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                               NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

  std::string message(messageBuffer, size);

  modio::writeLogLine("Error while using " + error_function + ": " + message, MODIO_DEBUGLEVEL_ERROR);

  //Free the buffer.
  LocalFree(messageBuffer);
}
#endif

void removeEmptyDirectory(std::string path)
{
#ifdef LINUX
  if (remove(path.c_str()))
    writeLogLine(path + " removed", MODIO_DEBUGLEVEL_LOG);
  else
    writeLogLine("Could not remove " + path, MODIO_DEBUGLEVEL_ERROR);
#endif

#ifdef OSX
  if (remove(path.c_str()))
    writeLogLine(path + " removed", MODIO_DEBUGLEVEL_LOG);
  else
    writeLogLine("Could not remove " + path, MODIO_DEBUGLEVEL_ERROR);
#endif

#ifdef WINDOWS
  if (!RemoveDirectory(path.c_str()))
    writeLastErrorLog("RemoveDirectory");
#endif
}

#ifdef WINDOWS
int deleteDirectoryWindows(const std::string &refcstrRootDirectory)
{
  HANDLE hFile;                    // Handle to directory
  std::string strFilePath;         // Filepath
  std::string strPattern;          // Pattern
  WIN32_FIND_DATA FileInformation; // File information

  strPattern = refcstrRootDirectory + "\\*.*";
  hFile = ::FindFirstFile(strPattern.c_str(), &FileInformation);
  if (hFile != INVALID_HANDLE_VALUE)
  {
    do
    {
      if (FileInformation.cFileName[0] != '.')
      {
        strFilePath.erase();
        strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;

        if (FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
          // Delete subdirectory
          int iRC = deleteDirectoryWindows(strFilePath);
          if (iRC)
            return iRC;
        }
        else
        {
          // Set file attributes
          if (::SetFileAttributes(strFilePath.c_str(),
                                  FILE_ATTRIBUTE_NORMAL) == FALSE)
            return ::GetLastError();

          // Delete file
          if (::DeleteFile(strFilePath.c_str()) == FALSE)
            return ::GetLastError();
        }
      }
    } while (::FindNextFile(hFile, &FileInformation) == TRUE);

    // Close handle
    ::FindClose(hFile);

    DWORD dwError = ::GetLastError();
    if (dwError != ERROR_NO_MORE_FILES)
      return dwError;
    else
    {
      // Set directory attributes
      if (::SetFileAttributes(refcstrRootDirectory.c_str(),
                              FILE_ATTRIBUTE_NORMAL) == FALSE)
        return ::GetLastError();

      // Delete directory
      if (::RemoveDirectory(refcstrRootDirectory.c_str()) == FALSE)
        return ::GetLastError();
    }
  }
  return 0;
}
#endif

std::string getModIODirectory()
{
  return modio::addSlashIfNeeded(ROOT_PATH) + ".modio/";
}

std::vector<std::string> getFilenames(std::string directory)
{
  std::vector<std::string> filenames;
  struct dirent *ent;
  DIR *dir;
  if (directory[directory.size() - 1] != '/')
    directory += '/';

  if ((dir = opendir(directory.c_str())) != NULL)
  {
    while ((ent = readdir(dir)) != NULL)
    {
      DIR *current_dir;
      std::string current_file_path = directory + ent->d_name;
      if ((current_dir = opendir(current_file_path.c_str())) != NULL && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
      {
        std::vector<std::string> subdirectories_filenames = getFilenames(directory + ent->d_name);
        for (int i = 0; i < (int)subdirectories_filenames.size(); i++)
        {
          filenames.push_back(std::string(ent->d_name) + "/" + subdirectories_filenames[i]);
        }
        closedir(current_dir);
      }
      else if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
      {
        filenames.push_back(ent->d_name);
      }
    }
    closedir(dir);
  }
  return filenames;
}

void createDirectory(std::string directory)
{
  writeLogLine("Creating directory " + directory, MODIO_DEBUGLEVEL_LOG);
#ifdef LINUX
  mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

#ifdef OSX
  mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

#ifdef WINDOWS
  if (!CreateDirectory((char *)directory.c_str(), NULL))
    writeLastErrorLog("CreateDirectory");
#endif
}

bool removeDirectory(std::string directory_name)
{
#ifdef WINDOWS
  int error_code = deleteDirectoryWindows(directory_name);
  if (error_code != 0)
    modio::writeLogLine("Could not remove directory, error code: " + modio::toString(error_code), MODIO_DEBUGLEVEL_ERROR);
  return error_code == 0;
#endif

  DIR *dir;
  struct dirent *entry;
  char path[PATH_MAX];

  if (directory_name[directory_name.size() - 1] != '/')
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
      snprintf(path, (size_t)PATH_MAX, "%s%s", directory_name.c_str(), entry->d_name);
      if (opendir(path) != NULL)
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

void removeFile(std::string filename)
{
  if (remove(filename.c_str()) != 0)
    writeLogLine("Could not remove " + filename, MODIO_DEBUGLEVEL_ERROR);
  else
    writeLogLine(filename + " removed", MODIO_DEBUGLEVEL_LOG);
}

double getFileSize(std::string file_path)
{
  double file_size = 0;
  FILE *fp = fopen(file_path.c_str(), "rb");
  if (fp)
  {
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    file_size = ftell(fp);
    fclose(fp);
  }
  return file_size;
}

void createPath(std::string path)
{
  std::string current_path;
  u32 slash_position;

  while (path.length())
  {
    slash_position = (int)path.find('/');
    if (slash_position == (u32)std::string::npos)
      break;
    current_path += path.substr(0, slash_position) + "/";
    path.erase(path.begin(), path.begin() + slash_position + 1);
    createDirectory(current_path);
  }
}
} // namespace modio
