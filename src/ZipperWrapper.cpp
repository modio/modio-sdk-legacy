#include "ZipperWrapper.h"

void extract(string zip_path, string directory_path)
{
  Unzipper unzipper(zip_path);
  std::vector<ZipEntry> entries = unzipper.entries();
  unzipper.extract(directory_path);
  unzipper.close();
}
