#include "dependencies/minizip/minizip.h"

uLong filetime(const char *filename, tm_zip *tmzip, uLong *dostime)
{
    int ret = 0;
#ifdef _WIN32
    FILETIME ftLocal;
    HANDLE hFind;
    WIN32_FIND_DATAA ff32;

    hFind = FindFirstFileA(filename, &ff32);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        FileTimeToLocalFileTime(&(ff32.ftLastWriteTime), &ftLocal);
        FileTimeToDosDateTime(&ftLocal,((LPWORD)dostime)+1,((LPWORD)dostime)+0);
        FindClose(hFind);
        ret = 1;
    }
#else
#if defined unix || defined __APPLE__
    struct stat s = {0};
    struct tm* filedate;
    time_t tm_t = 0;

    if (strcmp(filename,"-") != 0)
    {
        char name[MAXFILENAME+1];
        int len = strlen(filename);
        if (len > MAXFILENAME)
            len = MAXFILENAME;

        strncpy(name, filename, MAXFILENAME - 1);
        name[MAXFILENAME] = 0;

        if (name[len - 1] == '/')
            name[len - 1] = 0;

        /* not all systems allow stat'ing a file with / appended */
        if (stat(name,&s) == 0)
        {
            tm_t = s.st_mtime;
            ret = 1;
        }
    }

    filedate = localtime(&tm_t);

    tmzip->tm_sec  = filedate->tm_sec;
    tmzip->tm_min  = filedate->tm_min;
    tmzip->tm_hour = filedate->tm_hour;
    tmzip->tm_mday = filedate->tm_mday;
    tmzip->tm_mon  = filedate->tm_mon ;
    tmzip->tm_year = filedate->tm_year;
#endif
#endif
    return ret;
}

int check_file_exists(const char* filename)
{
	FILE* ftestexist;
	ftestexist = fopen(filename, "rb");
    if (ftestexist == NULL)
        return 0;
    fclose(ftestexist);
    return 1;
}

int is_large_file(const char* filename)
{
    ZPOS64_T pos = 0;
	FILE* pFile;
	pFile = fopen(filename, "rb");

    if (pFile == NULL)
        return 0;

    FSEEKO_FUNC(pFile, 0, SEEK_END);
    pos = FTELLO_FUNC(pFile);
    fclose(pFile);

    modio::writeLogLine("File: " + std::string(filename) + " is " + modio::toString((u32)pos), MODIO_DEBUGLEVEL_LOG);

    return (pos >= 0xffffffff);
}

/* Calculate the CRC32 of a file, because to encrypt a file, we need known the CRC32 of the file before */
int get_file_crc(const char* filenameinzip, void *buf, unsigned long size_buf, unsigned long* result_crc)
{
    FILE *fin = NULL;
    unsigned long calculate_crc = 0;
    unsigned long size_read = 0;
    int err = ZIP_OK;

    fin = fopen(filenameinzip,"rb");
    if (fin == NULL)
        err = ZIP_ERRNO;
    else
    {
        do
        {
            size_read = (int)fread(buf,1,size_buf,fin);

            if ((size_read < size_buf) && (feof(fin) == 0))
            {
                modio::writeLogLine("Could not read " + std::string(filenameinzip), MODIO_DEBUGLEVEL_ERROR);
                err = ZIP_ERRNO;
            }

            if (size_read > 0)
                calculate_crc = crc32(calculate_crc,(Bytef*)buf,size_read);
        }
        while ((err == ZIP_OK) && (size_read > 0));
    }

    if (fin)
        fclose(fin);

    modio::writeLogLine("File " + std::string(filenameinzip) + " crc " + modio::toString((u32)calculate_crc), MODIO_DEBUGLEVEL_LOG);
    *result_crc = calculate_crc;
    return err;
}
