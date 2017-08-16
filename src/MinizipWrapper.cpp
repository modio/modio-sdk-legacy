#include "MinizipWrapper.h"

void extract(string zip_path, string directory_path)
{
  unzFile zipfile = unzOpen( zip_path.c_str() );
  unz_global_info global_info;
  char read_buffer[ READ_SIZE ];

  uLong i;
  for ( i = 0; i < global_info.number_entry; ++i )
  {
    unz_file_info file_info;
    char filename[ MAX_FILENAME ];
    if ( unzGetCurrentFileInfo(
        zipfile,
        &file_info,
        filename,
        MAX_FILENAME,
        NULL, 0, NULL, 0 ) != UNZ_OK)
    {
      unzClose(zipfile);
      return;
    }

    const size_t filename_length = strlen(filename);
    if (filename[ filename_length-1 ] == dir_delimter)
    {
      string file_path = directory_path + "/" + filename;
      mkdir(file_path.c_str() , S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    else
    {
      string file_path = directory_path + "/" + filename;
      FILE *out = fopen( file_path.c_str(), "wb" );
      int error = UNZ_OK;
      do
      {
        error = unzReadCurrentFile(zipfile, read_buffer, READ_SIZE);

        if (error > 0)
        {
            fwrite( read_buffer, error, 1, out );
        }
      } while (error > 0);

      fclose(out);
    }

    unzCloseCurrentFile( zipfile );

    if((i+1) < global_info.number_entry)
    {
        if(unzGoToNextFile(zipfile) != UNZ_OK)
        {
            unzClose(zipfile);
            return;
        }
    }
  }
  unzClose(zipfile);
}
