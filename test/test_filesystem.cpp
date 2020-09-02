#include "Utility.h"
#include "gtest/gtest.h"
#include "ghc/filesystem.hpp"
#include "Fixture_CleanupFolders.h"

class FolderBase : public Fixture_CleanupFolders{};
TEST_F(FolderBase, CreateRelativeSubfolderFailure)
{
  bool result = modio::createDirectory("folder/subfolder");
  EXPECT_FALSE(result) << "We should fail to create subdirectories when folders doesn't exist";
  EXPECT_FALSE(modio::directoryExists("folder/subfolder") ) << "Folder " << " shouldn't exists";
  EXPECT_FALSE(modio::directoryExists("folder/subfolder/")) << "Folder shouldn't exists";

  // Same result should be with slash at end
  result = modio::createDirectory("folder/subfolder/");
  EXPECT_FALSE(result) << "We should fail to create subdirectories when folders doesn't exist with a slash at the end";
  EXPECT_FALSE(modio::directoryExists("folder/subfolder/")) << "Folder shouldn't exists";
  EXPECT_FALSE(modio::directoryExists("folder/subfolder")) << "Folder shouldn't exists";

  result = modio::createDirectory(u8"folder/чизкейк");
  EXPECT_FALSE(result) << "Try to create a subfolder directory with unicode folder name";
  result = modio::directoryExists(u8"folder/чизкейк");
  EXPECT_FALSE(result) << u8"Folder folder/чизкейк shouldn't exists";
  result = modio::directoryExists(u8"folder/чизкейк/");
  EXPECT_FALSE(result) << u8"Folder folder/чизкейк/ shouldn't exists";

  result = modio::createDirectory(u8"чизкейк/subfolder");
  EXPECT_FALSE(result) << "Try to create a subfolder directory with unicode in the base folder name";
  result = modio::directoryExists(u8"чизкейк/subfolder");
  EXPECT_FALSE(result) << u8"Folder чизкейк/subfolder shouldn't exists";
  result = modio::directoryExists(u8"чизкейк/subfolder/");
  EXPECT_FALSE(result) << u8"Folder чизкейк/subfolder/ shouldn't exists";
}

TEST_F(FolderBase, CreateRelativeFolderSuccess)
{
  bool result = modio::createDirectory("folder");
  EXPECT_TRUE(result) << "Failed to create directory folder";
  EXPECT_TRUE(modio::directoryExists("folder")) << "Folder folder should exist";
  EXPECT_TRUE(modio::directoryExists("folder/")) << "Folder folder/ should exist";

  result = modio::createDirectory("folderWithSlash/");
  EXPECT_TRUE(result) << "Failed to create directory";
  EXPECT_TRUE(modio::directoryExists("folderWithSlash")) << "Folder folderWithSlash should exist";
  EXPECT_TRUE(modio::directoryExists("folderWithSlash/")) << "Folder folderWithSlash/ should exist";

  result = modio::createDirectory(u8"чизкейк");
  EXPECT_TRUE(result) << "Try to create a directory with unicode folder name";
  result = modio::directoryExists(u8"чизкейк");
  EXPECT_TRUE(result) << u8"Folder чизкейк should exists";
  result = modio::directoryExists(u8"чизкейк/");
  EXPECT_TRUE(result) << u8"Folder чизкейк/ should exists";
}

static void createFolderTest( const std::string& subfolder, bool forwardSlash = true )
{
  ghc::filesystem::path wd = ghc::filesystem::current_path();
  std::string path = wd.generic_u8string() + ( forwardSlash ? "/" : "\\" ) + subfolder;
  bool result = modio::createDirectory(path);
  EXPECT_TRUE(result) << "Failed to create directory " << path;
  EXPECT_TRUE(modio::directoryExists(path)) << "Folder " << path << " should exist";
}

static void createFolderFailureTest( const std::string& subfolder, bool forwardSlash = true )
{
  ghc::filesystem::path wd = ghc::filesystem::current_path();
  std::string path = wd.generic_u8string() + ( forwardSlash ? "/" : "\\" ) + subfolder;
  bool result = modio::createDirectory(path);
  EXPECT_FALSE(result) << "Failed to create directory " << path;
  EXPECT_FALSE(modio::directoryExists(path)) << "Folder " << path << " should exist";
}

TEST_F(FolderBase, CreateRelativeFolderFailure)
{
  createFolderTest("directory");
  setFilePermission("directory", false);
  createFolderFailureTest("directory/subdirectry");
  
  createFolderTest(u8"модио");
  setFilePermission(u8"модио", false);
  createFolderFailureTest(u8"модио/shouldExist");
}

TEST_F(FolderBase, CreateAbsoluteFolderSuccess)
{
  // Create directories with forwardslashes in their paths
  createFolderTest("subfolder");
  createFolderTest("pathWithSlash/");
  createFolderTest("pathWithBackslash\\");
  createFolderTest(u8"ジャクソン");
  createFolderTest(u8"スラッシュジャクソン/");
  createFolderTest(u8"バックソン\\");

  DeleteTransientDirectories();

  // Create directories with backslash in their paths
  createFolderTest("subfolder", false);
  createFolderTest("pathWithSlash/", false);
  createFolderTest("pathWithBackslash\\", false);
  createFolderTest(u8"ジャクソン", false);
  createFolderTest(u8"スラッシュジャクソン/", false);
  createFolderTest(u8"バックソン\\", false);
}

TEST_F(FolderBase, CreateRelativeSubfolderSuccess)
{
  bool result = modio::createDirectory("folder");
  EXPECT_TRUE(modio::directoryExists("folder")) << "folder should exists";

  result = modio::createDirectory("folder/subfolder");
  EXPECT_TRUE(result) << "Failed to create folder/subfolder";
  EXPECT_TRUE(modio::directoryExists("folder/subfolder")) << "Folder folder/subfolder should exist";
  EXPECT_TRUE(modio::directoryExists("folder/subfolder/")) << "Folder folder/subfolder/ should exist";

  result = modio::createDirectory("folder/subfolderWithSlash/");
  EXPECT_TRUE(result) << "Failed to create folder/subfolderWithSlash/";
  EXPECT_TRUE(modio::directoryExists("folder/subfolderWithSlash")) << "Folder folder/subfolderWithSlash exist";
  EXPECT_TRUE(modio::directoryExists("folder/subfolderWithSlash/")) << "Folder folder/subfolderWithSlash/ exist";

  result = modio::createDirectory(u8"folder/чизкейк");
  EXPECT_TRUE(result) << "Try to create a subfolder directory with unicode folder name";
  result = modio::directoryExists(u8"folder/чизкейк");
  EXPECT_TRUE(result) << u8"Folder folder/чизкейк should exists";
  result = modio::directoryExists(u8"folder/чизкейк/");
  EXPECT_TRUE(result) << u8"Folder folder/чизкейк/ should exists";

  result = modio::createDirectory(u8"чизкейк");
  EXPECT_TRUE(result) << "Try to create a folder with unicode folder name";
  result = modio::directoryExists(u8"чизкейк");
  EXPECT_TRUE(result) << u8"Folder чизкейк should exists";

  result = modio::createDirectory(u8"чизкейк/subfolder");
  EXPECT_TRUE(result) << "Try to create a subfolder directory with unicode in the base folder name";
  result = modio::directoryExists(u8"чизкейк/subfolder");
  EXPECT_TRUE(result) << u8"Folder чизкейк/subfolder should exists";
  result = modio::directoryExists(u8"чизкейк/subfolder/");
  EXPECT_TRUE(result) << u8"Folder чизкейк/subfolder/ should exists";

  result = modio::createDirectory(u8"чизкейк/subfolderWithSlash/");
  EXPECT_TRUE(result) << "Try to create a subfolder directory with unicode in the base folder name";
  result = modio::directoryExists(u8"чизкейк/subfolderWithSlash");
  EXPECT_TRUE(result) << u8"Folder чизкейк/subfolderWithSlash should exists";
  result = modio::directoryExists(u8"чизкейк/subfolderWithSlash/");
  EXPECT_TRUE(result) << u8"Folder чизкейк/subfolderWithSlash/ should exists";
}

static void createRelativePathTest( const std::string& relativePath )
{
  bool result = modio::createPath(relativePath);
  EXPECT_TRUE(modio::directoryExists(relativePath)) << "Failed to create a subfolder " << relativePath << " in the base folder name";
  result = modio::directoryExists(relativePath);
  EXPECT_TRUE(result) << u8"Folder " << relativePath << " should exists";
}

TEST_F(FolderBase, CreateRelativePathSuccess)
{
  createRelativePathTest("hi/");
  createRelativePathTest(u8"чизкейк/");
  // This test verifies that we get a true result when creating a test where the folder already exists
  createRelativePathTest(u8"чизкейк/");
  createRelativePathTest(u8"hi/");
  // Test unicode
  createRelativePathTest(u8"バックソン/");
  // Test creating nested structure
  createRelativePathTest(u8"a/b/c/");
  // Test creating nested structure with slash at end
  createRelativePathTest(u8"d/e/f/");
  // This test verifies that we get a true result when creating a nested a test where the folder already exists
  createRelativePathTest(u8"d/e/f/");
  // This test verifies that we get a true result when creating a nested a test where part of the folder already exists
  createRelativePathTest(u8"d/e/f/g/h/");
  // Test nested unicode
  createRelativePathTest(u8"バックソン/unicode/");
  createRelativePathTest(u8"unicode/バックソン/");
}

static void createRelativePathWithFilename(const std::string& relativePath, const std::string& parentFolder)
{
  bool result = modio::createPath(relativePath);
  EXPECT_TRUE(modio::directoryExists(parentFolder)) << "Failed to create a folder " << parentFolder << " when supplying path with filename";
  result = modio::directoryExists(parentFolder);
  EXPECT_TRUE(result) << u8"Folder " << parentFolder << " should exists";
}

TEST_F(FolderBase, CreateRelativePathWithFilenameSuccess)
{
  createRelativePathWithFilename("hi/poop.txt", "hi");
  createRelativePathWithFilename(u8"poop.txt", ghc::filesystem::current_path().generic_u8string());
  createRelativePathWithFilename(u8"чизкейк.txt", ghc::filesystem::current_path().generic_u8string());
  // This test verifies that we get a true result when creating a test where the folder already exists
  createRelativePathWithFilename(u8"hi/cheese.txt", "hi" );
  // This test verifies that we get a true result when creating a test where the folder already exists with a unicode filename
  createRelativePathWithFilename(u8"hi/чизкейк.txt", "hi");
  // This test verifies that we get a true result when creating a test where the folder already exists with a unicode filename
  createRelativePathWithFilename(u8"hi/mi/чизкейк.txt", "hi/mi");
  createRelativePathWithFilename(u8"чизкейк/mi/чизкейк.txt", u8"чизкейк/mi");
}
