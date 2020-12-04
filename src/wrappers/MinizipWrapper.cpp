#include "wrappers/MinizipWrapper.h"
#include <stdio.h>                                     // for NULL, fclose
#include <stdlib.h>                                    // for free, malloc
#include <string.h>                                    // for strcat, strcpy
#include <iostream>                                    // for char_traits
#include "c/ModioC.h"                                  // for MODIO_DEBUGLEV...
#include "miniz.h"                                     // for MAX_WBITS, Z_D...
#include "Utility.h"                       // for writeLogLine
#include "ghc/filesystem.hpp"

#ifdef MODIO_WINDOWS_DETECTED
#define USEWIN32IOAPI
#include "dependencies/minizip/iowin32.c"
#include "../WindowsFilesystem.h"
#endif
#include "dependencies/minizip/minizip.h"  // for filetime, is_l...
#include "dependencies/minizip/unzip.h"    // for unzClose, unzC...
#include "dependencies/minizip/zip.h"      // for ZIP_OK, zipClose
#include "../Filesystem.h"

static const std::uint32_t UTF8_FLAG = (1<<11);

namespace modio
{
namespace minizipwrapper
{
void extract(std::string zip_path, std::string directory_path)
{
  directory_path = addSlashIfNeeded(directory_path);
  
#ifdef USEWIN32IOAPI
  zlib_filefunc64_def ffunc = { 0 };
#endif

  writeLogLine(std::string("Extracting ") + zip_path, MODIO_DEBUGLEVEL_LOG);
#ifdef USEWIN32IOAPI
  fill_win32_filefunc64W(&ffunc);
  unzFile zipfile = unzOpen2_64(modio::platform::utf8ToWstr(zip_path).c_str(), &ffunc);
#else
  unzFile zipfile = unzOpen(zip_path.c_str());
#endif

  if (zipfile == NULL)
  {
    writeLogLine("Cannot open " + zip_path, MODIO_DEBUGLEVEL_ERROR);
    return;
  }

  unz_global_info global_info;
  unzGetGlobalInfo(zipfile, &global_info);
  char read_buffer[READ_SIZE];

  uLong i;
  for (i = 0; i < global_info.number_entry; ++i)
  {
    unz_file_info file_info;

    int err;
    std::string utf8_encoded_filename;
    char final_filename[MAX_FILENAME];
    // Ensure that filename isn't used after this scope
    {
		char filename[MAX_FILENAME];

		err = unzGetCurrentFileInfo(
			zipfile,
			&file_info,
			filename,
			MAX_FILENAME,
			NULL, 0, NULL, 0);

		if (err != UNZ_OK)
		{
			unzClose(zipfile);
			writeLogLine("error " + toString(err) + " with zipfile in unzGetCurrentFileInfo", MODIO_DEBUGLEVEL_ERROR);
			return;
		}
    
        // Is the name encoded in UTF8 or CP437
        if(file_info.flag & UTF8_FLAG)
        {
            utf8_encoded_filename = filename;
        }
        else
        {
            utf8_encoded_filename = modio::CP437ToUTF8(filename);
        }
    }

    strcpy(final_filename, directory_path.c_str());
    strcat(final_filename, utf8_encoded_filename.c_str());

    modio::createPath(directory_path + utf8_encoded_filename);
    
    if (utf8_encoded_filename[utf8_encoded_filename.size()-1] == dir_delimter)
    {
      modio::createDirectory(final_filename);
    }
    else
    {
      err = unzOpenCurrentFile(zipfile);

      if (err != UNZ_OK)
      {
        writeLogLine(std::string("Cannot open ") + utf8_encoded_filename, MODIO_DEBUGLEVEL_ERROR);
        return;
      }

      FILE *out;
      out = modio::platform::fopen(final_filename, "wb");

      if (!out)
      {
        writeLogLine(std::string("error opening ") + utf8_encoded_filename, MODIO_DEBUGLEVEL_ERROR);
        return;
      }

      err = UNZ_OK;
      do
      {
        err = unzReadCurrentFile(zipfile, read_buffer, READ_SIZE);
        if (err < 0)
        {
          writeLogLine("error " + toString(err) + " with zipfile in unzReadCurrentFile", MODIO_DEBUGLEVEL_ERROR);
          unzCloseCurrentFile(zipfile);
          unzClose(zipfile);
          return;
        }
        if (err > 0)
        {
          if (fwrite(read_buffer, (size_t)err, 1, out) != 1)
          {
            writeLogLine("error " + toString(err) + " in writing extracted file", MODIO_DEBUGLEVEL_ERROR);
          }
        }
      } while (err > 0);

      fclose(out);

      err = unzCloseCurrentFile(zipfile);
      if (err != UNZ_OK)
        writeLogLine("error " + toString(err) + " with " + utf8_encoded_filename + " in unzCloseCurrentFile", MODIO_DEBUGLEVEL_ERROR);
    }

    if ((i + 1) < global_info.number_entry)
    {
      err = unzGoToNextFile(zipfile);

      if (err != UNZ_OK)
      {
        writeLogLine("error " + toString(err) + " with zipfile in unzGoToNextFile", MODIO_DEBUGLEVEL_ERROR);
        unzClose(zipfile);
        return;
      }
    }
  }
  unzClose(zipfile);
  writeLogLine(zip_path + " extracted", MODIO_DEBUGLEVEL_LOG);
}

void getFileTimeWrapper( const std::string& fileName, zip_fileinfo& out_fileInfo )
{
  std::error_code ec;
  ghc::filesystem::directory_entry fileInfo(fileName, ec);
  if( !ec )
  {
    auto lastWriteTime = fileInfo.last_write_time();
    std::time_t ctime = decltype(lastWriteTime)::clock::to_time_t(lastWriteTime);

    struct tm* filedate = localtime(&ctime);

    out_fileInfo.dosDate = 0;
    out_fileInfo.tmz_date.tm_sec = filedate->tm_sec;
    out_fileInfo.tmz_date.tm_min = filedate->tm_min;
    out_fileInfo.tmz_date.tm_hour = filedate->tm_hour;
    out_fileInfo.tmz_date.tm_mday = filedate->tm_mday;
    out_fileInfo.tmz_date.tm_mon = filedate->tm_mon;
    out_fileInfo.tmz_date.tm_year = filedate->tm_year;
  }
}

bool getIsLargeFile( const std::string& fileName )
{
  std::error_code ec;
  ghc::filesystem::directory_entry fileInfo(fileName, ec);
  if( !ec )
  {
    return fileInfo.file_size() > 0xffffffff;
  }
  // If the file doesn't exist, it's not a large file
  return false;
}

void compressFiles(std::string root_directory, std::vector<std::string> filenames, std::string zip_path)
{
  // Users might pass in directories without slashes, and we use root_directory + filename in a few places
  root_directory = modio::addSlashIfNeeded(root_directory);

  writeLogLine("Compressing " + modio::toString((u32)filenames.size()) + " files", MODIO_DEBUGLEVEL_LOG);

  writeLogLine(std::string("Compressing ") + " into " + zip_path, MODIO_DEBUGLEVEL_LOG);

  zipFile zf = NULL;
  #ifdef USEWIN32IOAPI
    zlib_filefunc64_def ffunc = {0};
  #endif
  const char *zipfilename = zip_path.c_str();
  const char *password = NULL;
  void *buf = NULL;
  size_t size_buf = WRITEBUFFERSIZE;
  int errclose = 0;
  int err = 0;
  int opt_overwrite = APPEND_STATUS_CREATE;
  int opt_compress_level = 9;
  int opt_exclude_path = 0;

  buf = malloc(size_buf);
  if (buf == NULL)
  {
    writeLogLine("Error allocating memory", MODIO_DEBUGLEVEL_ERROR);
  }

  #ifdef USEWIN32IOAPI
    fill_win32_filefunc64W(&ffunc);
    zf = zipOpen2_64(modio::windows_platform::utf8ToWstr(zip_path).c_str(), opt_overwrite, NULL, &ffunc);
  #else
    zf = zipOpen64(zipfilename, opt_overwrite);
  #endif

  if (zf == NULL)
  {
    writeLogLine(std::string("Could not open ") + zipfilename, MODIO_DEBUGLEVEL_ERROR);
  }
  else
  {
    writeLogLine(std::string("Creating ") + zipfilename, MODIO_DEBUGLEVEL_LOG);
  }

  for (size_t i = 0; i < filenames.size(); i++)
  {
    if (filenames[i] == "modio.json")
      continue;
    std::string filename = filenames[i];
    std::string complete_file_path = root_directory + filename;
    FILE *fin = NULL;
    size_t size_read = 0;
    const char *filenameinzip = filename.c_str();
    const char *savefilenameinzip;
    zip_fileinfo zi = { };
    unsigned long crcFile = 0;
    int zip64 = 0;

    /* Get information about the file on disk so we can store it in zip */
    getFileTimeWrapper(complete_file_path, zi);
    zip64 = getIsLargeFile(complete_file_path);

    /* Construct the filename that our file will be stored in the zip as.
          The path name saved, should not include a leading slash.
          If it did, windows/xp and dynazip couldn't read the zip file. */
    savefilenameinzip = filenameinzip;
    while (savefilenameinzip[0] == '\\' || savefilenameinzip[0] == '/')
      savefilenameinzip++;
    /* Should the file be stored with any path info at all? */
    if (opt_exclude_path)
    {
      const char *tmpptr = NULL;
      const char *lastslash = 0;

      for (tmpptr = savefilenameinzip; *tmpptr; tmpptr++)
      {
        if (*tmpptr == '\\' || *tmpptr == '/')
          lastslash = tmpptr;
      }

      if (lastslash != NULL)
        savefilenameinzip = lastslash + 1; /* base filename follows last slash. */
    }

    // @MarkusR: Updated this call from zipOpenNewFileInZip3_64 for UTF-8 support, 36 and UTF8_FLAG (1<<11) comes from
    // https://stackoverflow.com/questions/14625784/how-to-convert-minizip-wrapper-to-unicode
    /* Add to zip file */
    err = zipOpenNewFileInZip4_64(zf, savefilenameinzip, &zi,
                                  NULL, 0, NULL, 0, NULL /* comment*/,
                                  (opt_compress_level != 0) ? Z_DEFLATED : 0,
                                  opt_compress_level, 0,
                                  /* -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, */
                                  -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                                  password, crcFile, 36, UTF8_FLAG,zip64);

    if (err != ZIP_OK)
      writeLogLine(std::string("Could not open ") + filenameinzip + " in zipfile, zlib error: " + toString(err), MODIO_DEBUGLEVEL_ERROR);
    else
    {
      fin = modio::platform::fopen(complete_file_path.c_str(), "rb");
      if (fin == NULL)
      {
        writeLogLine(std::string("Could not open ") + filenameinzip + " for reading", MODIO_DEBUGLEVEL_ERROR);
      }
    }

    if (err == ZIP_OK)
    {
      /* Read contents of file and write it to zip */
      do
      {
        size_read = fread(buf, 1, size_buf, fin);
        if ((size_read < size_buf) && (feof(fin) == 0))
        {
          writeLogLine(std::string("Error in reading ") + filenameinzip, MODIO_DEBUGLEVEL_ERROR);
        }

        if (size_read > 0)
        {
          err = zipWriteInFileInZip(zf, buf, (unsigned int)size_read);
          if (err < 0)
          {
            writeLogLine(std::string("Error in writing ") + filenameinzip + " in zipfile, zlib error: " + toString(err), MODIO_DEBUGLEVEL_ERROR);
          }
        }
      } while ((err == ZIP_OK) && (size_read > 0));
    }

    if (fin)
      fclose(fin);

    if (err < 0)
      err = ZIP_ERRNO;
    else
    {
      err = zipCloseFileInZip(zf);
      if (err != ZIP_OK)
        writeLogLine(std::string("Error in closing ") + filenameinzip + " in zipfile, zlib error: " + toString(err), MODIO_DEBUGLEVEL_ERROR);
    }
  }

  errclose = zipClose(zf, NULL);

  if (errclose != ZIP_OK)
    writeLogLine(std::string("Error in closing ") + zipfilename + ", zlib error: " + toString(errclose), MODIO_DEBUGLEVEL_ERROR);

  free(buf);
}

void compressDirectory(std::string directory, std::string zip_path)
{
  directory = modio::addSlashIfNeeded(directory);
  writeLogLine("Compressing directory " + directory, MODIO_DEBUGLEVEL_LOG);
  compressFiles(directory, getFilenames(directory), zip_path);
}
}
}
