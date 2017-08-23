#ifndef MINIZIP_WRAPPER_H
#define MINIZIP_WRAPPER_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "minizip/unzip.h"
#include "Utility.h"

#define dir_delimter '/'
#define MAX_FILENAME 512
#define READ_SIZE 8192

using namespace std;

namespace modworks
{
  void extract(string zip_path, string directory_path);
}

#endif
