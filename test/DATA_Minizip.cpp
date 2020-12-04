#include "DATA_Minizip.h"

namespace modio
{
  std::map<std::string, std::string> fileToContent =
  {
    { u8"Modell-höhlenspinne-s.obj", "Ö is a bad character" },
    { "modio.txt", "is awesome" },
    { "jackson.txt", "contains awesomeness" },
    { "extensionlessFile", "Extensionless files can be a problem" },
    { u8"модио.txt", "This filename has unicode characters in it, don't do this at home kids" },
    { u8"folder/модио.txt", "This filename has unicode characters in it but reside in a ansi folder" },
    { u8"folder\\backslash.txt", "This folder is defined by backslash and not forward slash" },
    { u8"folder\\バックスラッシュ.txt", "This folder is defined by backslash and not forward slash and have unicode characters in filename" },
    { u8"ユニコード/unicode.txt", "This this folder has unicode characters in it" },
    { u8"ユニコード/ファイル.txt", "This this folder and file has unicode characters in it" },
    { u8"ユニコード/延長なし", "This this folder has unicode characters in it and file has no extension" },
  };
}