#include "c++/ModIOInstance.h"
#include "gtest/gtest.h"
#include "Utility.h"
#include "Fixture_CleanupFolders.h"
#include "../src/WindowsFilesystem.h"
#include "dependencies/minizip/minizip.h"
#include "c++/schemas/Response.h"
#include "c++/schemas/Mod.h"
#include <algorithm>
#include "Globals.h"

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

void InitTestConfig( u32 environment, u32 game_id, bool retrieve_mods_from_other_games, bool polling_enabled, const std::string& api_key, const std::string& root_path, std::string expected_root_path = "", std::string expected_gamedir_path = "" )
{
  expected_root_path = expected_root_path.empty() ? root_path : expected_root_path;

  modio::Instance modio_instance(environment, game_id, retrieve_mods_from_other_games, polling_enabled, api_key, root_path);
  EXPECT_EQ(modio::MODIO_URL, environment == MODIO_ENVIRONMENT_TEST ? "https://api.test.mod.io/" : "https://api.mod.io/");
  EXPECT_EQ(modio::API_KEY, api_key);
  EXPECT_EQ(modio::GAME_ID, game_id);
  EXPECT_EQ(modio::ROOT_PATH, expected_root_path);
  EXPECT_EQ(modio::ADDITIONAL_GAMEDIR_PATH, expected_gamedir_path);
  EXPECT_EQ(modio::RETRIEVE_MODS_FROM_OTHER_GAMES, retrieve_mods_from_other_games);
  EXPECT_EQ(modio::POLLING_ENABLED, polling_enabled);
}

void InitTestConfigC(u32 environment, u32 game_id, bool retrieve_mods_from_other_games, bool polling_enabled, const char* api_key, const char* root_path, std::string expected_root_path = "", std::string expected_gamedir_path = "")
{
  // If we pass in nullptr here, we should ensure that desiredRootPath doesn't get assigned a nullptr
  std::string desiredRootPath = root_path ? root_path : "";
  expected_root_path = expected_root_path.empty() ? desiredRootPath : expected_root_path;

  modioInit(environment, game_id, retrieve_mods_from_other_games, polling_enabled, api_key, root_path);
  EXPECT_EQ(modio::MODIO_URL, environment == MODIO_ENVIRONMENT_TEST ? "https://api.test.mod.io/" : "https://api.mod.io/");
  EXPECT_EQ(modio::API_KEY, api_key ? api_key : "");
  EXPECT_EQ(modio::GAME_ID, game_id);
  EXPECT_EQ(modio::ROOT_PATH, expected_root_path);
  EXPECT_EQ(modio::ADDITIONAL_GAMEDIR_PATH, expected_gamedir_path);
  EXPECT_EQ(modio::RETRIEVE_MODS_FROM_OTHER_GAMES, retrieve_mods_from_other_games);
  EXPECT_EQ(modio::POLLING_ENABLED, polling_enabled);
}

TEST_F(Modio, TestInitAfterShutdown)
{
  u32 game_id_a = 7;
  std::string apikey_a("e91c01b8882f4affeddd56c96111977b");
  std::string root_a("");
  bool retrive_mods_from_other_games_a = false;
  bool polling_enabled_a = false;
  
  u32 game_id_b = 8;
  std::string apikey_b("BadAPIKey");
  std::string root_b("RootB/");
  bool retrive_mods_from_other_games_b = true;
  bool polling_enabled_b = true;

  InitTestConfig(MODIO_ENVIRONMENT_TEST, game_id_a, retrive_mods_from_other_games_a, polling_enabled_a, apikey_a, root_a);
  InitTestConfig(MODIO_ENVIRONMENT_LIVE, game_id_b, retrive_mods_from_other_games_b, polling_enabled_b, apikey_b, root_b);
  // Do A again to ensure that flipping back also gives us correct results
  InitTestConfig(MODIO_ENVIRONMENT_TEST, game_id_a, retrive_mods_from_other_games_a, polling_enabled_a, apikey_a, root_a);
  // Ensure that we don't init in root_b
  modio::removeDirectory(root_b);
  modio::createPath(root_b);
  setFilePermission(root_b, false);
  InitTestConfig(MODIO_ENVIRONMENT_LIVE, game_id_b, retrive_mods_from_other_games_b, polling_enabled_b, apikey_b, root_b, modio::getMyDocumentsPath(), "game_" + std::to_string(game_id_b) );
  // Ensure that root b is correctly setup if we init in it now
  setFilePermission(root_b, true);
  InitTestConfig(MODIO_ENVIRONMENT_LIVE, game_id_b, retrive_mods_from_other_games_b, polling_enabled_b, apikey_b, root_b);

  // Ensure that we don't init in root_b
  modio::removeDirectory(root_b);
  modio::createPath(root_b);
  setFilePermission(root_b, false);
  InitTestConfig(MODIO_ENVIRONMENT_LIVE, game_id_b, retrive_mods_from_other_games_b, polling_enabled_b, apikey_b, root_b, modio::getMyDocumentsPath(), "game_" + std::to_string(game_id_b));
  // Ensure that root b is correctly setup if we init in it now
  setFilePermission(root_b, true);
  InitTestConfigC(MODIO_ENVIRONMENT_LIVE, game_id_b, retrive_mods_from_other_games_b, polling_enabled_b, apikey_b.c_str(), nullptr);
  // Test with nullptr on api-key
  InitTestConfigC(MODIO_ENVIRONMENT_LIVE, game_id_b, retrive_mods_from_other_games_b, polling_enabled_b, nullptr, nullptr);
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

static std::string downloadedImageFilenameUnicode = u8"downloaded/логотип_оригинал.png";

void onDownloadImage_TestDownloadImageUnicode(void* object, ModioResponse response)
{
  bool* wait = (bool*)object;

  ASSERT_EQ(response.code, 200);
  EXPECT_EQ(response.result_count, 0);
  EXPECT_EQ(response.result_cached, 0);
  EXPECT_EQ(response.result_limit, 0);
  EXPECT_EQ(response.result_offset, -1);
  EXPECT_EQ(response.result_total, 0);

  EXPECT_TRUE(modio::fileExists(downloadedImageFilenameUnicode));
  EXPECT_EQ(calculateCRCOfFile(downloadedImageFilenameUnicode), 1624551240); // CRC calculated off line and verified against https://simplycalc.com/crc32-file.php

  *wait = false;
}

static void onGetMod_TestDownloadImageUnicode(void* object, ModioResponse response, ModioMod mod)
{
  ASSERT_EQ(response.code, 200);

  // Ensure that the path to the filename exists before we try to download it
  modio::createPath(downloadedImageFilenameUnicode);
  modioDownloadImage(object, mod.logo.original, downloadedImageFilenameUnicode.c_str(), &onDownloadImage_TestDownloadImageUnicode);
}

TEST_F(Modio, TestDownloadImageUnicode)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 171, false, false, "2f5a33fc9c1786d231ff60e2227fad03", "");

  bool wait = true;

  modioGetMod(&wait, 865, &onGetMod_TestDownloadImageUnicode);

  while (wait)
  {
    // @todo: A timeout would be great here
    modioProcess();
  }

  modioShutdown();
}

TEST_F(Modio, TestInstallMods)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 171, false, false, "2f5a33fc9c1786d231ff60e2227fad03", u8"огурец");

  volatile static bool finished = false;

  auto wait = [&]() {
    while (!finished)
    {
      modio_instance.sleep(10);
      modio_instance.process();
    }
  };

  auto finish = [&]() {
    finished = true;
  };

  modio_instance.downloadMod(865);
  modio_instance.setDownloadListener([&](u32 response_code, u32 mod_id) {
    ASSERT_EQ(response_code, 200);

    std::string zipLocation = modio::getModIODirectory() + "tmp/865_modfile.zip";

    ASSERT_TRUE( modio::fileExists(zipLocation) );
    EXPECT_EQ( calculateCRCOfFile(zipLocation), 4070914100 );

    modio_instance.installDownloadedMods();

    std::string modFolder = modio::getModIODirectory() + "/mods/865";
    ASSERT_TRUE(modio::directoryExists(modFolder));
    EXPECT_TRUE(modio::fileExists(modFolder + "/demo.txt"));
    EXPECT_TRUE(modio::fileExists(modFolder + "/modio.json"));
    EXPECT_TRUE(modio::fileExists(modFolder + "/__MACOSX/._demo.txt"));

    EXPECT_EQ(calculateCRCOfFile(modFolder + "/demo.txt"), 1873862126);
    EXPECT_EQ(calculateCRCOfFile(modFolder + "/__MACOSX/._demo.txt"), 2818760342);
    // @todo: Verify values in modio.json file

    finish();
  });

  wait();
}

// We can't test subscribing/unsubscribing without beeing part of the team for the game, so we would need to
// provide a logged in user key
#if 0
TEST_F(Modio, TestSubscribeMod)
{
  modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 171, "2f5a33fc9c1786d231ff60e2227fad03");

  volatile static bool finished = false;

  auto wait = [&]() {
    while (!finished)
    {
      modio_instance.sleep(10);
      modio_instance.process();
    }
  };

  auto finish = [&]() {
    finished = true;
  };

  modio_instance.subscribeToMod(864, [&](const modio::Response& response, const modio::Mod& mod) {
    EXPECT_EQ(response.code, 401);
    EXPECT_EQ(response.result_cached, 0);
    EXPECT_EQ(response.result_count, 0);
    EXPECT_EQ(response.result_limit, 0);
    EXPECT_EQ(response.result_offset, 0);
    EXPECT_EQ(response.result_total, 0);

    EXPECT_EQ(response.result_cached, 0);
    EXPECT_EQ(response.result_count, 0);
    EXPECT_EQ(response.result_limit, 0);
    EXPECT_EQ(response.result_offset, 0);
    EXPECT_EQ(response.result_total, 0);

    EXPECT_EQ(mod.date_added, 1516086822);
    EXPECT_EQ(mod.date_live, 1516086822);
    EXPECT_EQ(mod.date_updated, 1568712676);
    EXPECT_EQ(mod.description, "");
    EXPECT_EQ(mod.description_plaintext, "");
    EXPECT_EQ(mod.game_id, 171);
    EXPECT_EQ(mod.homepage_url, "");
    EXPECT_EQ(mod.id, 864);
    EXPECT_EQ(mod.logo.filename, "mod7.2.png");
    EXPECT_EQ(mod.logo.original, "https://image.test.modcdn.io/mods/1fc2/864/mod7.2.png");
    EXPECT_EQ(mod.logo.thumb_320x180, "https://thumb.test.modcdn.io/mods/1fc2/864/crop_320x180/mod7.2.png");
    EXPECT_EQ(mod.logo.thumb_640x360, "https://thumb.test.modcdn.io/mods/1fc2/864/crop_640x360/mod7.2.png");
    EXPECT_EQ(mod.logo.thumb_1280x720, "https://thumb.test.modcdn.io/mods/1fc2/864/crop_1280x720/mod7.2.png");
    EXPECT_EQ(mod.maturity_option, 0);
    EXPECT_EQ(mod.media.images.size(), 0);
    EXPECT_EQ(mod.media.sketchfab.size(), 0);
    EXPECT_EQ(mod.media.youtube.size(), 0);
    EXPECT_EQ(mod.metadata_blob, "");
    EXPECT_EQ(mod.metadata_kvps.size(), 0);

    EXPECT_EQ(mod.modfile.changelog.c_str(), "");
    EXPECT_EQ(mod.modfile.date_added, 1516086834);
    EXPECT_EQ(mod.modfile.date_scanned, 0);
    EXPECT_EQ(mod.modfile.download.binary_url, "https://test.mod.io/mods/file/865");
    EXPECT_EQ(mod.modfile.download.date_expires, 1662113157);
    EXPECT_EQ(mod.modfile.filehash.md5, "07eff700ac20d9d0ce27f7b9de4ba494");
    EXPECT_EQ(mod.modfile.filename, "demo.zip");
    EXPECT_EQ(mod.modfile.filesize, 589);
    EXPECT_EQ(mod.modfile.id, 865);
    EXPECT_EQ(mod.modfile.metadata_blob.size(), 0);
    EXPECT_EQ(mod.modfile.mod_id, 864);
    EXPECT_EQ(mod.modfile.version, "6.7.1");
    EXPECT_EQ(mod.modfile.virus_positive, 0);
    EXPECT_EQ(mod.modfile.virus_status, 0);
    EXPECT_EQ(mod.modfile.virustotal_hash.c_str(), "");

    EXPECT_EQ(mod.name, "Mod #7");
    EXPECT_EQ(mod.name_id, "mod7");
    EXPECT_EQ(mod.profile_url, "https://example.test.mod.io/mod7");

    // We don't verify the stats fields, as they might be updated
    
    EXPECT_EQ(mod.submitted_by.avatar.filename, "avatar.png");
    EXPECT_EQ(mod.submitted_by.avatar.original, "https://static.test.mod.io/v1/images/default/avatar.png");
    EXPECT_EQ(mod.submitted_by.avatar.thumb_100x100, "https://static.test.mod.io/v1/images/default/avatar_100x100.png");
    EXPECT_EQ(mod.submitted_by.avatar.thumb_50x50, "https://static.test.mod.io/v1/images/default/avatar_50x50.png");
    EXPECT_EQ(mod.submitted_by.date_online, 1596004914); // Potentially exclude this as someone might log into the account
    EXPECT_EQ(mod.submitted_by.id, 31591);
    EXPECT_EQ(mod.submitted_by.language, "");
    EXPECT_EQ(mod.submitted_by.name_id, "testuser");
    EXPECT_EQ(mod.submitted_by.profile_url, "https://test.mod.io/members/testuser");
    EXPECT_EQ(mod.submitted_by.timezone, "");
    EXPECT_EQ(mod.submitted_by.username, "testuser");
    
    EXPECT_EQ(mod.summary, "This is a demonstration mod profile, to show how mod.io looks and feels.");
    EXPECT_EQ(mod.visible, 1);

    ASSERT_EQ(mod.tags.size(), 5);
   
    std::list<modio::Tag> expectedTags = { 
      { 1516086822, "Autumn" }, 
      { 1516086822, "Player" },
      { 1516186765, "Prop" },
      { 1516186765, "Script" },
      { 1516186765, "Singleplayer" }
    };

    EXPECT_TRUE( std::equal( mod.tags.begin(), mod.tags.end(), expectedTags.begin(), []( auto&& l, auto&& r )
      { return l.date_added == r.date_added && l.name == r.name; } ) );

    finish();
    });

  wait();
}

TEST_F(Modio, TestUnsubscribeMod)
{
}
#endif