#include "Utility.h"
#include <errno.h>                               // for errno
#include <fcntl.h>                               // for SEEK_END
#include <limits.h>                              // for PATH_MAX
#include <stdio.h>                               // for remove, fclose, fopen
#include <string.h>                              // for strcmp, NULL, size_t
#include <sys/stat.h>                            // for mkdir, S_IROTH, S_IRWXG
#include <array>                                 // for array
#include <chrono>                                // for milliseconds, durati...
#include <ctime>                                 // for time
#include <fstream>                               // for operator<<, ofstream
#include <iomanip>                               // for operator<<, setw
#include <string>                                // for string, operator+
#include <vector>                                // for allocator, vector
#include "Globals.h"                             // for ACCESS_TOKEN, VERSION
#include "c/ModioC.h"                            // for MODIO_DEBUGLEVEL_LOG
#include "dependencies/minizip/minizip.h"        // for check_file_exists

#ifdef MODIO_LINUX_DETECTED
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <ext/alloc_traits.h>                    // for __alloc_traits<>::va...
#endif

#ifdef MODIO_WINDOWS_DETECTED
#  ifdef MODIO_UE4_DETECTED 
#    include <Windows/MinWindows.h>
#  else
#    include <windows.h>
#  endif
#  include <strsafe.h>
#  include "dependencies/dirent/dirent.h"
//#include "vld.h"
#endif

#ifdef MODIO_OSX_DETECTED
#include <sys/stat.h>
#include <dirent.h>
#endif

namespace modio
{

#ifdef MODIO_WINDOWS_DETECTED
static wchar_t *WideCharFromString(std::string const &str)
{
  // returns the number of required wchar_t WITHOUT terminating NUL
  size_t rl = mbstowcs(NULL, str.c_str(), 0);
  wchar_t *wcstr = (wchar_t *)malloc((rl + 1) * sizeof *wcstr);
  mbstowcs(wcstr, str.c_str(), INT_MAX);
  return wcstr;
}

static std::string StringFromWideChar(wchar_t const *str)
{
  // returns the number of required bytes WITHOUT terminating NUL
  size_t rl = wcstombs(NULL, str, 0);
  char *cstr = (char *)malloc(rl + 1);
  wcstombs(cstr, str, INT_MAX);
  std::string ret(cstr);
  free(cstr);
  return ret;
}
#endif

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
  for (size_t i = 0; i < temp.length(); i++)
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

std::string replaceSubstrings(const std::string &str, const std::string &from, const std::string &to)
{
  std::string return_value = str;

  if (from == "")
    return return_value;

  size_t start_pos = 0;
  while ((start_pos = return_value.find(from, start_pos)) != std::string::npos)
  {
    return_value.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
  return return_value;
}

std::string addSlashIfNeeded(const std::string &directory_path)
{
  std::string return_value = directory_path;

  if (return_value != "" && return_value[return_value.size() - 1] != '/')
    return_value += "/";

  return return_value;
}

// Log methods

void writeLogLine(const std::string &text, u32 debug_level)
{
  // NOTE(@jackson): Lower value is higher severity (error == 0)
  if (DEBUG_LEVEL < debug_level)
    return;

  std::ofstream log_file(getModIODirectory() + "log.txt", std::ios::app);
  log_file << "[" << modio::getCurrentTimeSeconds() << "] ";
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
  std::ofstream log_file(getModIODirectory() + "log.txt");
  log_file.close();
}

// Time methods

u32 getCurrentTimeSeconds()
{
  return (u32)std::time(nullptr);
}

double getCurrentTimeMillis()
{
  std::chrono::milliseconds current_time =
  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
  return (double)current_time.count();
}

// Json methods

bool hasKey(nlohmann::json json_object, const std::string &key)
{
  return json_object.find(key) != json_object.end() && !json_object[key].is_null();
}

nlohmann::json toJson(const std::string &json_str)
{
  if (json_str == "")
    return "{}"_json;

  nlohmann::json response_json;
  try
  {
    response_json = nlohmann::json::parse(json_str);
  }
  catch (nlohmann::json::parse_error &e)
  {
    writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
    response_json = "{}"_json;
  }
  return response_json;
}

nlohmann::json openJson(const std::string &file_path)
{
  std::ifstream ifs(file_path);
  nlohmann::json cache_file_json;
  if (ifs.is_open())
  {
    try
    {
      ifs >> cache_file_json;
    }
    catch (nlohmann::json::parse_error &e)
    {
      modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
      cache_file_json = {};
    }
  }
  ifs.close();
  return cache_file_json;
}

void writeJson(const std::string &file_path, nlohmann::json json_object)
{
  std::ofstream ofs(file_path);
  ofs << std::setw(4) << json_object << std::endl;
  ofs.close();
}

// Filesystem methods

#ifdef MODIO_WINDOWS_DETECTED
static void writeLastErrorLog(const std::string &error_function)
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

#if defined(MODIO_LINUX_DETECTED) || defined(MODIO_OSX_DETECTED)
static void removeEmptyDirectory(const std::string &path)
{
  if (remove(path.c_str()))
    writeLogLine(path + " removed", MODIO_DEBUGLEVEL_LOG);
  else
    writeLogLine("Could not remove " + path, MODIO_DEBUGLEVEL_ERROR);
}
#endif

#ifdef MODIO_WINDOWS_DETECTED
static DWORD deleteDirectoryWindows(const std::string &refcstrRootDirectory)
{
  HANDLE hFile;                    // Handle to directory
  std::string strFilePath;         // Filepath
  std::string strPattern;          // Pattern
  WIN32_FIND_DATA FileInformation; // File information

  strPattern = refcstrRootDirectory + "\\*.*";
  wchar_t *strPattern_wc = WideCharFromString(strPattern);
  hFile = ::FindFirstFile(strPattern_wc, &FileInformation);
  free(strPattern_wc);
  if (hFile != INVALID_HANDLE_VALUE)
  {
    do
    {
      if ( wcscmp (FileInformation.cFileName, L".") != 0
          && wcscmp (FileInformation.cFileName, L"..") != 0)
      {
        std::wstring ws_filename(FileInformation.cFileName);
        std::string str_filename(ws_filename.begin(), ws_filename.end());

        writeLogLine("Deleting file: " + str_filename, MODIO_DEBUGLEVEL_LOG);

        strFilePath.erase();
        strFilePath = refcstrRootDirectory + "\\" + StringFromWideChar(FileInformation.cFileName);

        if (FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
          // Delete subdirectory
          DWORD iRC = deleteDirectoryWindows(strFilePath);
          if (iRC)
            return iRC;
        }
        else
        {
          // Set file attributes
          wchar_t *strFilePath_wc = WideCharFromString(strFilePath);
          if (::SetFileAttributes(strFilePath_wc, FILE_ATTRIBUTE_NORMAL) == FALSE)
          {
            free(strFilePath_wc);
            return ::GetLastError();
          }

          // Delete file
          if (::DeleteFile(strFilePath_wc) == FALSE)
          {
            free(strFilePath_wc);
            return ::GetLastError();
          }

          free(strFilePath_wc);
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
      wchar_t *refcstrRootDirectory_wc = WideCharFromString(refcstrRootDirectory);
      if (::SetFileAttributes(refcstrRootDirectory_wc, FILE_ATTRIBUTE_NORMAL) == FALSE)
      {
        free(refcstrRootDirectory_wc);
        return ::GetLastError();
      }

      // Delete directory
      if (::RemoveDirectory(refcstrRootDirectory_wc) == FALSE)
      {
        free(refcstrRootDirectory_wc);
        return ::GetLastError();
      }

      free(refcstrRootDirectory_wc);
    }
  }
  return 0;
}
#endif

std::string getModIODirectory()
{
  return modio::addSlashIfNeeded(ROOT_PATH) + ".modio/";
}

std::string getFilename(std::string file_path)
{
  size_t last_slash = file_path.find_last_of("/\\");
  if (last_slash == std::string::npos)
    return file_path;
  std::string filename = file_path.substr(last_slash + 1);
  return filename;
}

std::string getFileExtension(std::string path)
{
  size_t last_point = path.find_last_of(".");
  if (last_point == std::string::npos)
    return "";
  return path.substr(last_point + 1);
}

bool isDirectory(const std::string &directory)
{
  DIR *dir;
  if ((dir = opendir(modio::addSlashIfNeeded(directory).c_str())) != NULL)
  {
    closedir(dir);
    return true;
  }
  return false;
}

bool directoryExists(const std::string &path)
{
  if (path == "")
    return true;
  DIR *dir = opendir(modio::addSlashIfNeeded(path).c_str());
  if (dir)
  {
    closedir(dir);
    return true;
  }
  return false;
}

std::string getDirectoryPath(const std::string &filename)
{
  size_t found;
  found = filename.find_last_of("/\\");
  if (found == std::string::npos)
    return "";
  return modio::addSlashIfNeeded(filename.substr(0, found));
}

bool fileExists(const std::string &directory)
{
  return check_file_exists(directory.c_str());
}

std::vector<std::string> getFilenames(const std::string &directory)
{
  std::string directory_with_slash = modio::addSlashIfNeeded(directory);

  std::vector<std::string> filenames;

  struct dirent *ent;
  DIR *dir;
  if ((dir = opendir(directory_with_slash.c_str())) != NULL)
  {
    while ((ent = readdir(dir)) != NULL)
    {
      DIR *current_dir = NULL;
      std::string current_file_path = directory_with_slash + ent->d_name;
      if ((current_dir = opendir(current_file_path.c_str())) != NULL && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
      {
        std::vector<std::string> subdirectories_filenames = getFilenames(directory_with_slash + ent->d_name);
        for (size_t i = 0; i < subdirectories_filenames.size(); i++)
        {
          filenames.push_back(std::string(ent->d_name) + "/" + subdirectories_filenames[i]);
        }
      }
      else if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
      {
        filenames.push_back(ent->d_name);
      }
      if (current_dir)
        closedir(current_dir);
    }
    closedir(dir);
  }
  return filenames;
}

std::vector<std::string> getDirectoryNames(const std::string &root_directory)
{
  std::string directory_with_slash = modio::addSlashIfNeeded(root_directory);

  std::vector<std::string> filenames;

  struct dirent *ent;
  DIR *dir;
  if ((dir = opendir(directory_with_slash.c_str())) != NULL)
  {
    while ((ent = readdir(dir)) != NULL)
    {
      DIR *current_dir = NULL;
      std::string current_file_path = directory_with_slash + ent->d_name;
      if ((current_dir = opendir(current_file_path.c_str())) != NULL && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
      {
        filenames.push_back(ent->d_name);
      }
      if (current_dir)
        closedir(current_dir);
    }
    closedir(dir);
  }
  return filenames;
}

void createDirectory(const std::string &directory)
{
  if (modio::directoryExists(directory))
    return;

  writeLogLine("Creating directory " + directory, MODIO_DEBUGLEVEL_LOG);
#if defined(MODIO_LINUX_DETECTED) || defined(MODIO_OSX_DETECTED)
  mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

#ifdef MODIO_WINDOWS_DETECTED
  wchar_t *director_wc = WideCharFromString(directory);
  if (!CreateDirectory(director_wc, NULL))
    writeLastErrorLog("CreateDirectory");
  free(director_wc);
#endif
}

bool removeDirectory(const std::string &directory)
{
#ifdef MODIO_WINDOWS_DETECTED
  DWORD error_code = deleteDirectoryWindows(directory);
  if (error_code != 0)
    modio::writeLogLine("Could not remove directory, error code: " + modio::toString((u32)error_code), MODIO_DEBUGLEVEL_ERROR);
  return error_code == 0;
#else

  DIR *dir;
  struct dirent *entry;
  char path[PATH_MAX];

  std::string directory_with_slash = modio::addSlashIfNeeded(directory);

  dir = opendir(directory_with_slash.c_str());
  if (dir == NULL)
  {
    writeLogLine("Error opendir()", MODIO_DEBUGLEVEL_LOG);
    return false;
  }

  while ((entry = readdir(dir)) != NULL)
  {
    if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
    {
      snprintf(path, (size_t)PATH_MAX, "%s%s", directory_with_slash.c_str(), entry->d_name);
      DIR *subdir = opendir(path);
      if (subdir)
      {
        closedir(subdir);
        removeDirectory(path);
      }
      writeLogLine("Deleting: " + std::string(path), MODIO_DEBUGLEVEL_LOG);
      removeFile(path);
    }
  }
  closedir(dir);
  writeLogLine("Deleting: " + directory_with_slash, MODIO_DEBUGLEVEL_LOG);
  removeEmptyDirectory(directory_with_slash);

  return true;
#endif
}

void removeFile(const std::string &filename)
{
  if (remove(filename.c_str()) != 0)
  {
    writeLogLine("Could not remove: " + filename + " error code: " + modio::toString(errno), MODIO_DEBUGLEVEL_ERROR);
    writeLogLine(std::strerror(errno), MODIO_DEBUGLEVEL_ERROR);
  }
  else
    writeLogLine(filename + " removed", MODIO_DEBUGLEVEL_LOG);
}

double getFileSize(const std::string &file_path)
{
  double file_size = 0;
  FILE *fp = fopen(file_path.c_str(), "rb");
  if (fp)
  {
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    fclose(fp);
  }
  return file_size;
}

void createPath(const std::string &path)
{
  std::string current_path;
  std::string tokenized_path = path;
  size_t slash_position;

  while (tokenized_path.length())
  {
    slash_position = tokenized_path.find('/');
    if (slash_position == std::string::npos)
      break;
    current_path += tokenized_path.substr(0, slash_position) + "/";
    tokenized_path.erase(tokenized_path.begin(), tokenized_path.begin() + slash_position + 1);

    createDirectory(current_path);
  }
}

std::vector<std::string> getHeaders()
{
  std::vector<std::string> headers;
  headers.push_back("User-Agent: Modio-SDK-" + modio::VERSION);
  if (modio::ACCESS_TOKEN != "")
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
  return headers;
}

std::vector<std::string> getHeadersNoToken()
{
  std::vector<std::string> headers;
  headers.push_back("User-Agent: Modio-SDK-" + modio::VERSION);
  return headers;
}

std::vector<std::string> getUrlEncodedHeaders()
{
  std::vector<std::string> headers;
  headers.push_back("User-Agent: Modio-SDK-" + modio::VERSION);
  if (modio::ACCESS_TOKEN != "")
    headers.push_back("Authorization: Bearer " + modio::ACCESS_TOKEN);
  headers.push_back("Content-Type: application/x-www-form-urlencoded");
  return headers;
}

static const char base64_chars[] = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

std::string base64Encode(unsigned char const* bytes_to_encode, unsigned int in_len)
{
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = ( char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;
}

} // namespace modio
