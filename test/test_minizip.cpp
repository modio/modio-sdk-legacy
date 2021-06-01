#include "../src/Filesystem.h"
#include "DATA_Minizip.h"
#include "Utility.h"
#include "ghc/filesystem.hpp"
#include "wrappers/MinizipWrapper.h"
#include "gtest/gtest.h"
#include <fstream>

// I think these tests should be rewritten, as they are way to bloated, and bugs
// might be in the tests
class MinizipTests : public ::testing::Test {
protected:
  void SetUp() override {
    ghc::filesystem::remove_all("zip");
    ghc::filesystem::remove_all("unzip");
  }

  void TearDown() override {
    ghc::filesystem::remove_all("zip");
    ghc::filesystem::remove_all("unzip");
  }

  void createZipDataset(const std::map<std::string, std::string> &dataset,
                        const std::string &inFolder) {
    for (auto &it : dataset) {
      bool result = modio::createPath(inFolder + "/" + it.first);
      ASSERT_TRUE(result) << "Failed to create path " << it.first;
      if (!modio::isDirectory(it.first)) {
        std::ofstream file =
            modio::platform::ofstream(inFolder + "/" + it.first);
        file << it.second;
        file.close();
      }
    }
  }

  void compareZipFilenamesWithDataset(
      const std::map<std::string, std::string> &dataset,
      const std::string &zipFile) {
    std::vector<std::string> filenames =
        modio::minizipwrapper::getZipFilenames(zipFile);

    EXPECT_EQ(dataset.size(), filenames.size())
        << "dataset contains different amount of files than the zipfile";

    for (const auto &datasetIt : dataset) {
      std::string datasetFilePath(datasetIt.first.size(), ' ');

      // All files should have forward slashes in them according to 4.4.17.1
      // in https://pkware.cachefly.net/webdocs/casestudies/APPNOTE.TXT
      std::replace_copy(datasetIt.first.begin(), datasetIt.first.end(),
                        datasetFilePath.begin(), '\\', '/');
      bool found = false;
      for (const std::string &filename : filenames) {
        if (filename == datasetFilePath) {
          found = true;
          break;
        }
      }

      EXPECT_TRUE(found) << "Couldn't find the file " << datasetFilePath
                         << " in the zipfile";
    }

    for (const auto &filename : filenames) {
      bool found = false;
      for (const auto &datasetIt : dataset) {
        std::string datasetFilePath(datasetIt.first.size(), ' ');
        std::replace_copy(datasetIt.first.begin(), datasetIt.first.end(),
                          datasetFilePath.begin(), '\\', '/');

        if (filename == datasetFilePath) {
          found = true;
          break;
        }
      }

      EXPECT_TRUE(found) << "Found the filename " << filename
                         << " in the zipfile but not in the dataset";
    }
  }

  void compareZipDataset(const std::map<std::string, std::string> &dataset,
                         const std::vector<std::string> &files,
                         std::string filesPath) {
    filesPath = modio::addSlashIfNeeded(filesPath);

    EXPECT_EQ(dataset.size(), files.size())
        << "Dataset and file size different";
    compareDiscFilenamesWithDataset(dataset, files);

    for (const std::string &file : files) {
      std::string datasetContent;
      if (getDatasetFileContent(dataset, file, datasetContent)) {
        std::ifstream stream = modio::platform::ifstream(filesPath + file);
        ASSERT_TRUE(stream.is_open())
            << "Couldn't open file " << filesPath + file;

        std::string fileContent;
        stream.seekg(0, std::ios::end);
        fileContent.reserve(stream.tellg());
        stream.seekg(0, std::ios::beg);

        fileContent.assign(std::istreambuf_iterator<char>(stream),
                           std::istreambuf_iterator<char>());

        EXPECT_EQ(fileContent, datasetContent)
            << "File " << file
            << " content is different from the content that was written to "
               "disk";
      }
    }
  }

  bool compareDiscFilenamesWithDataset(
      const std::map<std::string, std::string> &dataset,
      const std::vector<std::string> &files) {
    for (const auto &fileIt : files) {
      const std::string &filename = fileIt;

      bool found = false;
      for (const auto &datasetIt : dataset) {
        std::string datasetFilePath(datasetIt.first.size(), ' ');
        // All files should have forward slashes in them according to 4.4.17.1
        // in https://pkware.cachefly.net/webdocs/casestudies/APPNOTE.TXT
        std::replace_copy(datasetIt.first.begin(), datasetIt.first.end(),
                          datasetFilePath.begin(), '\\', '/');

        if (datasetFilePath == filename) {
          found = true;
          break;
        }
      }

      EXPECT_TRUE(found)
          << "File " << filename
          << " has been created that wasn't supposed to have been created";
      // If the file wasn't present in the file set
      if (!found) {
        return false;
      }
    }

    for (const auto &datasetIt : dataset) {
      std::string datasetFilePath(datasetIt.first.size(), ' ');
      std::replace_copy(datasetIt.first.begin(), datasetIt.first.end(),
                        datasetFilePath.begin(), '\\', '/');

      bool found = false;
      for (const auto &fileIt : files) {
        const std::string &filename = fileIt;

        if (datasetFilePath == filename) {
          found = true;
          break;
        }
      }

      EXPECT_TRUE(found) << "File " << datasetFilePath
                         << " from dataset wasn't properly found";
      // If the file wasn't present in the file set
      if (!found) {
        return false;
      }
    }

    return true;
  }

  // Transforms the filename and the dataset filename to all slashes, so we get
  // same files independent on the slashing
  bool getDatasetFileContent(const std::map<std::string, std::string> &dataset,
                             std::string filename,
                             std::string &out_datasetContent) {
    // Convert all directory separators to /
    std::replace(filename.begin(), filename.end(), '\\', '/');
    for (const auto &it : dataset) {
      std::string datasetFilePath(it.first.size(), ' ');
      std::replace_copy(it.first.begin(), it.first.end(),
                        datasetFilePath.begin(), '\\', '/');

      if (filename == datasetFilePath) {
        out_datasetContent = it.second;
        return true;
      }
    }

    out_datasetContent = "";
    return false;
  }
};

// void extract(std::string zip_path, std::string directory_path);
// void compressDirectory(std::string directory, std::string zip_path);
// void compressFiles(std::string root_directory, std::vector<std::string>
// filenames, std::string zip_path);

TEST_F(MinizipTests, TestCompressFiles) {
  createZipDataset(modio::fileToContent, "zip");
  modio::minizipwrapper::compressFiles("zip", modio::getFilenames("zip"),
                                       "zippity.zip");

  compareZipFilenamesWithDataset(modio::fileToContent, "zippity.zip");

  modio::minizipwrapper::extract("zippity.zip", "unzip");

  std::vector<std::string> files;
  for (auto &it : ghc::filesystem::recursive_directory_iterator("unzip")) {
    if (!it.is_directory()) {
      files.push_back(
          ghc::filesystem::relative(it.path(), "unzip").generic_u8string());
    }
  }
  compareZipDataset(modio::fileToContent, files, "unzip");
}
