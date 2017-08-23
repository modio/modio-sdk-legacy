#include "MinizipWrapper.h"

void extract(string zip_path, string directory_path)
{
  unzFile zipfile = unzOpen( zip_path.c_str() );
  unz_global_info global_info;
  unzGetGlobalInfo( zipfile, &global_info );
  char read_buffer[ READ_SIZE ];

  uLong i;
  for ( i = 0; i < global_info.number_entry; ++i )
  {
    unz_file_info file_info;
    char filename[ MAX_FILENAME ];
	char final_filename[ MAX_FILENAME ];
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
	
	strcpy(final_filename,directory_path.c_str());
	strcat(final_filename,"/");
	strcat(final_filename,filename);
	
    const size_t filename_length = strlen(filename);
    if (filename[ filename_length-1 ] == dir_delimter)
    {
      createDirectory(final_filename);
    }
    else
    {
		unzOpenCurrentFile( zipfile );

		string new_file_path = filename;
		FILE *out = fopen( final_filename, "wb" );

		int error = UNZ_OK;
		do    
		{
			error = unzReadCurrentFile( zipfile, read_buffer, READ_SIZE );
			if ( error < 0 )
			{
				unzCloseCurrentFile( zipfile );
				unzClose( zipfile );
				return;
			}
			if ( error > 0 )
			{
				fwrite( read_buffer, error, 1, out );
			}
		} while ( error > 0 );

		fclose( out );
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

