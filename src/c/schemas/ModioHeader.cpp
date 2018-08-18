#include "c/schemas/ModioHeader.h"

extern "C"
{
  void modioInitHeader(ModioHeader* header, nlohmann::json header_json)
  {
    header->filename = NULL;
    if(modio::hasKey(header_json, "filename"))
    {
      std::string filename_str = header_json["filename"];
      header->filename = new char[filename_str.size() + 1];
      strcpy(header->filename, filename_str.c_str());
    }

    header->original = NULL;
    if(modio::hasKey(header_json, "original"))
    {
      std::string original_str = header_json["original"];
      header->original = new char[original_str.size() + 1];
      strcpy(header->original, original_str.c_str());
    }
  }

  void modioFreeHeader(ModioHeader* header)
  {
    if(header)
    {
      if(header->filename)
        delete[] header->filename;
      if(header->original)
        delete[] header->original;
    }
  }
}
