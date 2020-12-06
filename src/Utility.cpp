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
#include "utf8.h"

#include "Filesystem.h"                          // for Filesystem::...

#ifdef MODIO_LINUX_DETECTED
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <ext/alloc_traits.h>                    // for __alloc_traits<>::va...
#include <errno.h>                               // for constants of errno
#endif

#if defined(MODIO_LINUX_DETECTED) || defined(MODIO_OSX_DETECTED)
#include <pwd.h>                                 // for getting the users home path (getpwuid/getuid)
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

// This should be char32_t, but MSVS2017 don't support char32_t
// Table from https://www.unicode.org/Public/MAPPINGS/VENDORS/MICSFT/PC/CP437.TXT
static std::uint32_t CP437UTF32Table[] = {
	0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008,
	0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f, 0x0010, 0x0011,
	0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017, 0x0018, 0x0019, 0x001a,
	0x001b, 0x001c, 0x001d, 0x001e, 0x001f, 0x0020, 0x0021, 0x0022, 0x0023,
	0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x002b, 0x002c,
	0x002d, 0x002e, 0x002f, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035,
	0x0036, 0x0037, 0x0038, 0x0039, 0x003a, 0x003b, 0x003c, 0x003d, 0x003e,
	0x003f, 0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
	0x0048, 0x0049, 0x004a, 0x004b, 0x004c, 0x004d, 0x004e, 0x004f, 0x0050,
	0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059,
	0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f, 0x0060, 0x0061, 0x0062,
	0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006a, 0x006b,
	0x006c, 0x006d, 0x006e, 0x006f, 0x0070, 0x0071, 0x0072, 0x0073, 0x0074,
	0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007a, 0x007b, 0x007c, 0x007d,
	0x007e, 0x007f, 0x00c7, 0x00fc, 0x00e9, 0x00e2, 0x00e4, 0x00e0, 0x00e5,
	0x00e7, 0x00ea, 0x00eb, 0x00e8, 0x00ef, 0x00ee, 0x00ec, 0x00c4, 0x00c5,
	0x00c9, 0x00e6, 0x00c6, 0x00f4, 0x00f6, 0x00f2, 0x00fb, 0x00f9, 0x00ff,
	0x00d6, 0x00dc, 0x00a2, 0x00a3, 0x00a5, 0x20a7, 0x0192, 0x00e1, 0x00ed,
	0x00f3, 0x00fa, 0x00f1, 0x00d1, 0x00aa, 0x00ba, 0x00bf, 0x2310, 0x00ac,
	0x00bd, 0x00bc, 0x00a1, 0x00ab, 0x00bb, 0x2591, 0x2592, 0x2593, 0x2502,
	0x2524, 0x2561, 0x2562, 0x2556, 0x2555, 0x2563, 0x2551, 0x2557, 0x255d,
	0x255c, 0x255b, 0x2510, 0x2514, 0x2534, 0x252c, 0x251c, 0x2500, 0x253c,
	0x255e, 0x255f, 0x255a, 0x2554, 0x2569, 0x2566, 0x2560, 0x2550, 0x256c,
	0x2567, 0x2568, 0x2564, 0x2565, 0x2559, 0x2558, 0x2552, 0x2553, 0x256b,
	0x256a, 0x2518, 0x250c, 0x2588, 0x2584, 0x258c, 0x2590, 0x2580, 0x03b1,
	0x00df, 0x0393, 0x03c0, 0x03a3, 0x03c3, 0x00b5, 0x03c4, 0x03a6, 0x0398,
	0x03a9, 0x03b4, 0x221e, 0x03c6, 0x03b5, 0x2229, 0x2261, 0x00b1, 0x2265,
	0x2264, 0x2320, 0x2321, 0x00f7, 0x2248, 0x00b0, 0x2219, 0x00b7, 0x221a,
	0x207f, 0x00b2, 0x25a0, 0x00a0 };


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
  if( directoryEntry.exists( ec ) && !ec )
  {
      return directoryEntry.is_directory( ec ) && !ec;
  }
  return false;
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

bool createDirectory(const std::string& directory)
{
  std::error_code ec;
  bool result = ghc::filesystem::create_directory(directory, ec);
  if( !result && ec )
  {
    writeLogLine("Failed to create directory \"" + directory + "\" with error: " + ec.message(), MODIO_DEBUGLEVEL_WARNING);
    return false;
  }

  return true;
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
#elif defined(MODIO_LINUX_DETECTED) || defined(MODIO_OSX_DETECTED)
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


std::string CP437ToUTF8(const std::string& string)
{
	std::vector<std::uint32_t> utf32_string;
	utf32_string.resize(string.size());

	for (std::size_t i = 0; i < string.size(); ++i)
	{
		utf32_string[i] = CP437UTF32Table[(unsigned char)string[i]];
	}

	std::string result;
	utf8::utf32to8(utf32_string.begin(), utf32_string.end(), std::back_inserter(result));

	return result;
}


} // namespace modio
