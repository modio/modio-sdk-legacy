#include "c++/ModIOInstance.h"
#include "gtest/gtest.h"
#include "Utility.h"
#include "Fixture_CleanupFolders.h"
#include "../src/WindowsFilesystem.h"

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