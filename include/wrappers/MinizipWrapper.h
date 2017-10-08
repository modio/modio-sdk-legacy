#ifndef MODIO_MINIZIP_WRAPPER_H
#define MODIO_MINIZIP_WRAPPER_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "dependencies/minizip/unzip.h"
#include "dependencies/minizip/minizip.h"
#include "Utility.h"

#define dir_delimter '/'
#define MAX_FILENAME 512
#define READ_SIZE 8192

using namespace std;

namespace modio
{
  namespace minizipwrapper
  {
    void extract(string zip_path, string directory_path);
    void compress(string directory, string zip_path);
  }
}

#endif
