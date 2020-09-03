#ifndef MODIO_TEST_CLEANUPFOLDERS_H
#define MODIO_TEST_CLEANUPFOLDERS_H

#include "ghc/filesystem.hpp"
#include "gtest/gtest.h"

class Fixture_CleanupFolders : public ::testing::Test
{
protected:
  void setFilePermission(std::string fileName, bool access);

  // Used for teardown to delete directories that we created
  static bool isAllowedDirectory(const ghc::filesystem::path& path)
  {
    for (auto& allowedFolder : allowedFolders)
    {
      if (ghc::filesystem::current_path().append(allowedFolder) == path)
      {
        return true;
      }
    }
    return false;
  }

  virtual void TearDown() override
  {
    DeleteTransientDirectories();
  }

  virtual void SetUp() override
  {
    DeleteTransientDirectories();
  }

  void DeleteTransientDirectories();

  static std::vector<std::string> allowedFolders;
};

#endif