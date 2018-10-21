#include "wrappers/MinizipWrapper.h"

namespace modio
{
namespace minizipwrapper
{
void extract(std::string zip_path, std::string directory_path)
{
  directory_path = addSlashIfNeeded(directory_path);
  
  writeLogLine(std::string("Extracting ") + zip_path, MODIO_DEBUGLEVEL_LOG);
  unzFile zipfile = unzOpen(zip_path.c_str());

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
    char filename[MAX_FILENAME];
    char final_filename[MAX_FILENAME];

    int err = unzGetCurrentFileInfo(
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

    strcpy(final_filename, directory_path.c_str());
    strcat(final_filename, filename);

    const size_t filename_length = strlen(filename);
    modio::createPath(directory_path + filename);
    
    if (filename[filename_length - 1] == dir_delimter)
    {
      createDirectory(final_filename);
    }
    else
    {
      err = unzOpenCurrentFile(zipfile);

      if (err != UNZ_OK)
      {
        writeLogLine(std::string("Cannot open ") + filename, MODIO_DEBUGLEVEL_ERROR);
        return;
      }

      std::string new_file_path = filename;
      FILE *out;
      out = fopen(final_filename, "wb");

      if (!out)
      {
        writeLogLine(std::string("error opening ") + final_filename, MODIO_DEBUGLEVEL_ERROR);
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
          if (fwrite(read_buffer, err, 1, out) != 1)
          {
            writeLogLine("error " + toString(err) + " in writing extracted file", MODIO_DEBUGLEVEL_ERROR);
          }
        }
      } while (err > 0);

      fclose(out);

      err = unzCloseCurrentFile(zipfile);
      if (err != UNZ_OK)
        writeLogLine("error " + toString(err) + " with " + filename + " in unzCloseCurrentFile", MODIO_DEBUGLEVEL_ERROR);
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

void compressFiles(std::string root_directory, std::vector<std::string> filenames, std::string zip_path)
{
  writeLogLine("Compressing " + modio::toString((u32)filenames.size()) + " files", MODIO_DEBUGLEVEL_LOG);

  writeLogLine(std::string("Compressing ") + " into " + zip_path, MODIO_DEBUGLEVEL_LOG);

  zipFile zf = NULL;
  //#ifdef USEWIN32IOAPI
  //  zlib_filefunc64_def ffunc = {0};
  //#endif
  char *zipfilename = (char *)zip_path.c_str();
  const char *password = NULL;
  void *buf = NULL;
  int size_buf = WRITEBUFFERSIZE;
  int errclose = 0;
  int err = 0;
  int opt_overwrite = APPEND_STATUS_CREATE;
  int opt_compress_level = 9;
  int opt_exclude_path = 0;

  buf = (void *)malloc(size_buf);
  if (buf == NULL)
  {
    writeLogLine("Error allocating memory", MODIO_DEBUGLEVEL_ERROR);
  }

  //#ifdef USEWIN32IOAPI
  //  fill_win32_filefunc64A(&ffunc);
  //  zf = zipOpen2_64(zipfilename, opt_overwrite, NULL, &ffunc);
  //#else
  zf = zipOpen64(zipfilename, opt_overwrite);
  //#endif

  if (zf == NULL)
  {
    writeLogLine(std::string("Could not open ") + zipfilename, MODIO_DEBUGLEVEL_ERROR);
  }
  else
  {
    writeLogLine(std::string("Creating ") + zipfilename, MODIO_DEBUGLEVEL_LOG);
  }

  for (int i = 0; i < (int)filenames.size(); i++)
  {
    if (filenames[i] == "modio.json")
      continue;
    std::string filename = filenames[i];
    std::string complete_file_path = root_directory + filename;
    FILE *fin = NULL;
    int size_read = 0;
    const char *filenameinzip = filename.c_str();
    const char *savefilenameinzip;
    zip_fileinfo zi = {0};
    unsigned long crcFile = 0;
    int zip64 = 0;

    /* Get information about the file on disk so we can store it in zip */
    filetime(complete_file_path.c_str(), &zi.tmz_date, &zi.dosDate);
    zip64 = is_large_file(complete_file_path.c_str());

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

    /* Add to zip file */
    err = zipOpenNewFileInZip3_64(zf, savefilenameinzip, &zi,
                                  NULL, 0, NULL, 0, NULL /* comment*/,
                                  (opt_compress_level != 0) ? Z_DEFLATED : 0,
                                  opt_compress_level, 0,
                                  /* -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, */
                                  -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                                  password, crcFile, zip64);

    if (err != ZIP_OK)
      writeLogLine(std::string("Could not open ") + filenameinzip + " in zipfile, zlib error: " + toString(err), MODIO_DEBUGLEVEL_ERROR);
    else
    {
      fin = fopen(complete_file_path.c_str(), "rb");
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
        size_read = (int)fread(buf, 1, size_buf, fin);
        if ((size_read < size_buf) && (feof(fin) == 0))
        {
          writeLogLine(std::string("Error in reading ") + filenameinzip, MODIO_DEBUGLEVEL_ERROR);
        }

        if (size_read > 0)
        {
          err = zipWriteInFileInZip(zf, buf, size_read);
          if (err < 0)
            writeLogLine(std::string("Error in writing ") + filenameinzip + " in zipfile, zlib error: " + toString(err), MODIO_DEBUGLEVEL_ERROR);
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
  std::vector<std::string> filenames = getFilenames(directory);
  for(u32 i=0; i<filenames.size(); i++)
  {
    filenames[i] = filenames[i];
  }
  compressFiles(directory, filenames, zip_path);
}
}
}
