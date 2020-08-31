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
#include <iomanip>                               // for operator<<, setw
#include <string>                                // for string, operator+
#include <vector>                                // for allocator, vector
#include "Globals.h"                             // for ACCESS_TOKEN, VERSION
#include "c/ModioC.h"                            // for MODIO_DEBUGLEVEL_LOG
#include "ghc/filesystem.hpp"
#include <iostream>
#include "dependencies/nlohmann/json.hpp"

#include "Filesystem.h"                          // for Filesystem::...

#ifdef MODIO_LINUX_DETECTED
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <ext/alloc_traits.h>                    // for __alloc_traits<>::va...
#include <pwd.h>                                 // for getting the users home path (getpwuid/getuid)
#include <errno.h>                               // for constants of errno
#endif

#ifdef MODIO_WINDOWS_DETECTED
#  define USEWIN32IOAPI
#  ifdef MODIO_UE4_DETECTED 
#    include <Windows/MinWindows.h>
#  else
#    include <windows.h>
#    include <shlobj.h>
#  endif
#  include <strsafe.h>
#  include "WindowsFilesystem.h"
//#include "vld.h"
#endif

#ifdef MODIO_OSX_DETECTED
#include <sys/stat.h>
#include <dirent.h>
#endif

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

  std::ofstream log_file( modio::platform::ofstream(modio::getModIODirectory() + "log.txt", std::ios::app ) );
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
  std::ofstream log_file( modio::platform::ofstream(getModIODirectory() + "log.txt") );
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
  std::ifstream ifs( modio::platform::ifstream(file_path) );
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
  std::ofstream ofs( modio::platform::ofstream(file_path) );
  ofs << std::setw(4) << json_object << std::endl;
  ofs.close();
}

// Filesystem methods

#ifdef MODIO_WINDOWS_DETECTED

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

std::string getModIODirectory()
{
  return modio::addSlashIfNeeded(ROOT_PATH) + ".modio/" + modio::addSlashIfNeeded(ADDITIONAL_GAMEDIR_PATH);
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

bool isDirectory(const std::string& directory)
{
  std::error_code ec;
  ghc::filesystem::directory_entry directoryEntry(directory, ec);
  return directoryEntry.exists() && ghc::filesystem::is_directory(directoryEntry);
}

bool directoryExists(const std::string& filename)
{
  if(filename == "")
  {
    return true;
  }

  return isDirectory(filename);
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
  return ghc::filesystem::is_regular_file(directory);
}

std::vector<std::string> getFilenames(const std::string &directory)
{
  std::vector<std::string> files;

  ghc::filesystem::path directoryPath( directory );
  for( auto& p : ghc::filesystem::recursive_directory_iterator(directoryPath) )
  {
    if( !p.is_directory() )
    {
      files.push_back( ghc::filesystem::relative( p.path(), directoryPath ).generic_u8string() );
    }
  }

  return files;
}

std::vector<std::string> getDirectoryNames(const std::string &root_directory)
{
  std::vector<std::string> files;

  ghc::filesystem::path rootDirectoryPath(root_directory);
  for (auto& p : ghc::filesystem::directory_iterator(rootDirectoryPath))
  {
    if (p.is_directory())
    {
      files.push_back(ghc::filesystem::relative(p.path(), rootDirectoryPath).generic_u8string());
    }
  }

  return files;
}

bool removeDirectory(const std::string &directory)
{
  std::error_code ec;
  bool result = ghc::filesystem::remove_all( directory, ec ) != static_cast<std::uintmax_t>(-1) || !ec;
  if( ec )
  {
    writeLogLine( "Failed to delete directory \"" + directory + "\" with error: " + ec.message(), MODIO_DEBUGLEVEL_WARNING );
  }

  return result;
}

void removeFile(const std::string &filename)
{
  std::error_code ec;
  bool result = ghc::filesystem::remove(filename, ec);
  if ( !result && ec )
  {
    writeLogLine("Could not remove file \"" + filename + "\" with error: " + ec.message(), MODIO_DEBUGLEVEL_ERROR);
  }
  else if( result ) // Don't output anything if no file was deleted
  {
    writeLogLine("\"" + filename + "\" removed", MODIO_DEBUGLEVEL_LOG);
  }
}

double getFileSize(const std::string &file_path)
{ 
  double file_size = 0;
  std::error_code ec;
  ghc::filesystem::directory_entry file(file_path, ec);
  if( !ec && ghc::filesystem::is_regular_file( file ) && ghc::filesystem::exists( file.status() ) )
  {
    file_size = file.file_size();
  }

  return file_size;
}

bool createPath(const std::string &path_str)
{
  ghc::filesystem::path path( path_str );
  
  std::error_code ec;
  bool result = ghc::filesystem::create_directories( path.parent_path().native(), ec );

  if( !result && ec )
  {
    writeLogLine( "Failed to create path: \"" + path.parent_path().native() + "\" with error: " + ec.message(), MODIO_DEBUGLEVEL_ERROR );
    return false;
  }
  return true;
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

std::string getMyDocumentsPath()
{
#ifdef MODIO_WINDOWS_DETECTED
  PWSTR   ppsz_path;
  HRESULT handle = SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &ppsz_path);

  if ( !SUCCEEDED(handle) ) {
    // If we didn't succeed, ensure that we return a non null value
    return "";
  }

  std::wstring my_documents_path_wstring = ppsz_path;
  CoTaskMemFree(ppsz_path);
  std::replace(my_documents_path_wstring.begin(), my_documents_path_wstring.end(), '\\', '/');

  // Convert to UTF-8
  return modio::windows_platform::wstrToUtf8(my_documents_path_wstring);
#elif defined(MODIO_LINUX_DETECTED)
  // @todo: This will most likely also work on mac, but I prefer of taking the safe path and introduce that codepath
  // when I have been able to actually test that
  const char *homedir = getenv("HOME");
  if ( homedir == nullptr )
  {
    // check /etc/passwd for the homedir specified in there
    homedir = getpwuid( getuid() )->pw_dir;
  }
  // std::string shouldn't be constructed with a nullptr
  return homedir ? homedir : "";
#endif
  return "";
}

std::string randomString(u32 length)
{
  auto randchar = []() -> char
  {
    const char charset[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = (sizeof(charset) - 1);
    return charset[ rand() % max_index ];
  };
  std::string str(length,0);
  std::generate_n( str.begin(), length, randchar );
  return str;
}

} // namespace modio
