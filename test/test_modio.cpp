#include "c++/ModIOInstance.h"
#include "gtest/gtest.h"
#include "Utility.h"
#include "Fixture_CleanupFolders.h"
#include "../src/WindowsFilesystem.h"
#include "dependencies/minizip/minizip.h"

class Modio : public Fixture_CleanupFolders{};

static void expectDirectoryExists(const std::string& dir)
{
  bool exists = modio::directoryExists(dir);
  EXPECT_TRUE(exists) << dir << " directory should have been created";
}

static void assertDirectoryExists(const std::string& dir)
{
  bool exists = modio::directoryExists(dir);
  ASSERT_TRUE(exists) << dir << " directory should have been created";
}

static void assertDirectoryDontExists(const std::string& dir)
{
  bool exists = modio::directoryExists(dir);
  ASSERT_FALSE(exists) << dir << " directory should NOT have been created";
}

static void expectFileExists(const std::string& file)
{
  bool exists = modio::fileExists(file);
  EXPECT_TRUE(exists) << file << " file should have been created";
}

TEST_F(Modio, TestInitStandard)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, false, false, "e91c01b8882f4affeddd56c96111977b", "");

  assertDirectoryExists(".modio");
  expectDirectoryExists(".modio/cache");
  expectDirectoryExists(".modio/mods");
  expectDirectoryExists(".modio/tmp");
  expectFileExists(u8".modio/log.txt");
}

TEST_F(Modio, TestInitSubdirectory)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, false, false, "e91c01b8882f4affeddd56c96111977b", "subdirInit");

  assertDirectoryExists("subdirInit/.modio");
  expectDirectoryExists("subdirInit/.modio/cache");
  expectDirectoryExists("subdirInit/.modio/mods");
  expectDirectoryExists("subdirInit/.modio/tmp");
  expectFileExists(u8"subdirInit/.modio/log.txt");
}

TEST_F(Modio, TestInitSubdirectoryUnicode)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, false, false, "e91c01b8882f4affeddd56c96111977b", u8"модио");

  assertDirectoryExists(u8"модио/.modio");
  expectDirectoryExists(u8"модио/.modio/cache");
  expectDirectoryExists(u8"модио/.modio/mods");
  expectDirectoryExists(u8"модио/.modio/tmp");
  expectFileExists(u8"модио/.modio/log.txt");
}

TEST_F(Modio, TestInitSubdirectoryAlreadyExists)
{
  ghc::filesystem::create_directory(u8"модио");

  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, false, false, "e91c01b8882f4affeddd56c96111977b", u8"модио");

  assertDirectoryExists(u8"модио/.modio");
  expectDirectoryExists(u8"модио/.modio/cache");
  expectDirectoryExists(u8"модио/.modio/mods");
  expectDirectoryExists(u8"модио/.modio/tmp");
  expectFileExists(u8"модио/.modio/log.txt");
}

TEST_F(Modio, TestInitSubdirectoryNotWriteable)
{
  // Ensure that we start off with a clean slate so we don't have a cached folder here
  setFilePermission(modio::addSlashIfNeeded(modio::getMyDocumentsPath()) + ".modio/game_7", true);
  modio::removeDirectory(modio::addSlashIfNeeded(modio::getMyDocumentsPath()) + ".modio/game_7");

  ghc::filesystem::create_directory(u8"dir");
  setFilePermission( u8"dir", false );

  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, false, false, "e91c01b8882f4affeddd56c96111977b", u8"dir");

  assertDirectoryDontExists(u8"dir/.modio");
  assertDirectoryDontExists(u8"dir/.modio/cache");
  assertDirectoryDontExists(u8"dir/.modio/mods");
  assertDirectoryDontExists(u8"dir/.modio/tmp");

  assertDirectoryExists(modio::addSlashIfNeeded(modio::getMyDocumentsPath()) + ".modio/game_7/");
  expectDirectoryExists(modio::addSlashIfNeeded(modio::getMyDocumentsPath()) + ".modio/game_7/cache");
  expectDirectoryExists(modio::addSlashIfNeeded(modio::getMyDocumentsPath()) + ".modio/game_7/mods");
  expectDirectoryExists(modio::addSlashIfNeeded(modio::getMyDocumentsPath()) + ".modio/game_7/tmp");
  expectFileExists(modio::addSlashIfNeeded(modio::getMyDocumentsPath()) + ".modio/game_7/log.txt");

  setFilePermission(u8"dir", true);
  modio::removeDirectory("dir");
}

static void onGetMod_TestGetMod(void* object, ModioResponse response, ModioMod mod)
{
  bool* wait = (bool*)object;
  ASSERT_EQ(response.code, 200);
  EXPECT_EQ(response.result_count, 0);
  EXPECT_EQ(response.result_cached, 0);
  EXPECT_EQ(response.result_limit, 0);
  EXPECT_EQ(response.result_offset, -1);
  EXPECT_EQ(response.result_total, 0);

  EXPECT_EQ(mod.id, 865);
  EXPECT_STRCASEEQ(mod.name, u8"Mod #8");
  
  *wait = false;
}

TEST_F(Modio, TestGetMod)
{
    modioInit(MODIO_ENVIRONMENT_TEST, 171, false, false, "2f5a33fc9c1786d231ff60e2227fad03", "");

    bool wait = true;

    modioGetMod(&wait, 865, &onGetMod_TestGetMod);

    while (wait)
    {
      // @todo: A timeout would be great here
      modioProcess();
    }

    modioShutdown();
}

static std::string downloadedImageFilename = u8"downloaded/logo_original.png";

u32 calculateCRCOfFile( const std::string& file )
{
  static const uintmax_t READ_BUFFER_SIZE = 1024 * 64; // 64kb is the same a minizip read buffer

  uintmax_t dataRemaining = ghc::filesystem::file_size( file );
  char* readBuffer = new char[READ_BUFFER_SIZE];
  if( !readBuffer )
  {
    return -1;
  }

  std::ifstream fileStream = modio::platform::ifstream(file, std::ios_base::binary);
  if( !fileStream.is_open() )
  {
    delete[] readBuffer;
    return -1;
  }

  u32 crcValue = MZ_CRC32_INIT;
  while( dataRemaining )
  {
    uintmax_t readBytes = std::min<uintmax_t>( READ_BUFFER_SIZE, dataRemaining );

    fileStream.read( readBuffer, readBytes );
    crcValue = mz_crc32( crcValue, (const mz_uint8*)readBuffer, readBytes );

    dataRemaining -= readBytes;
  }

  fileStream.close();
  delete[] readBuffer;

  return crcValue;
}

void onDownloadImage_TestDownloadImage(void* object, ModioResponse response)
{
  bool* wait = (bool*)object;

  ASSERT_EQ(response.code, 200);
  EXPECT_EQ(response.result_count, 0);
  EXPECT_EQ(response.result_cached, 0);
  EXPECT_EQ(response.result_limit, 0);
  EXPECT_EQ(response.result_offset, -1);
  EXPECT_EQ(response.result_total, 0);

  EXPECT_TRUE(modio::fileExists(downloadedImageFilename));
  EXPECT_EQ(calculateCRCOfFile(downloadedImageFilename), 1624551240); // CRC calculated off line and verified against https://simplycalc.com/crc32-file.php

  *wait = false;
}

static void onGetMod_TestDownloadImage(void* object, ModioResponse response, ModioMod mod)
{
  ASSERT_EQ(response.code, 200);

  // Ensure that the path to the filename exists before we try to download it
  modio::createPath(downloadedImageFilename);
  modioDownloadImage(object, mod.logo.original, downloadedImageFilename.c_str(), &onDownloadImage_TestDownloadImage);
}

TEST_F(Modio, TestDownloadImage)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 171, false, false, "2f5a33fc9c1786d231ff60e2227fad03", "");

  bool wait = true;

  modioGetMod(&wait, 865, &onGetMod_TestDownloadImage);

  while (wait)
  {
    // @todo: A timeout would be great here
    modioProcess();
  }

  modioShutdown();
}