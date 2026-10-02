#include "compression/zip-utils.h"

#include "compression/compression.h"
#include "contrib/minizip/zip.h"
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>

namespace ankicpp {
namespace zip {
bool compress(std::vector<std::string> inputs, std::string output) {
  compressError = CompressError::NONE;

  std::filesystem ::path outPath = std::filesystem::path(output);

  zipFile myZipFile = zipOpen(outPath.c_str(), APPEND_STATUS_CREATE);

  if (myZipFile == NULL) {
    compressError = CompressError::MINIZIP_ERROR;
    return false;
  }

  for (size_t i = 0; i < inputs.size(); i++) {
    try {
      std::fstream inStream(inputs[i].data(), std::ios::binary | std::ios::in);
      const std::string filename = std::filesystem::path(inputs[i]).filename();
      if (!inStream.is_open()) {
        compressError = CompressError::FILE_NOT_FOUND_ERROR;
        std::cout << std::format("zip compress: Error opening the file {} for compression.\n",
                                 filename);
        return false;
      }

      inStream.exceptions(inStream.failbit | inStream.badbit);
      inStream.seekg(0, std::ios::end);
      long size = inStream.tellg();
      inStream.seekg(0, std::ios::beg);

      std::vector<char> buffer(size);

      inStream.read(&buffer[0], size);
      inStream.close();

      zip_fileinfo zfi = {0};

      if (ZIP_OK == zipOpenNewFileInZip(myZipFile, filename.c_str(), &zfi, NULL,
                                        0, NULL, 0, NULL, Z_DEFLATED,
                                        Z_DEFAULT_COMPRESSION)) {
        if (ZIP_OK !=
            zipWriteInFileInZip(myZipFile, size == 0 ? "" : &buffer[0], size)) {
          compressError = CompressError::MINIZIP_ERROR;
          std::cout << std::format(
              "zip compress: Error building the zipping of file {} in the apkg.\n", filename);
          return false;
        }

        if (ZIP_OK != zipCloseFileInZip(myZipFile)) {
          compressError = CompressError::MINIZIP_ERROR;
          std::cout << std::format(
              "zip compress: Error ending the zipping of file {} in the apkg.\n", filename);
          return false;
        }
      }
    } catch (const std::ifstream::failure &e) {
      std::cerr << std::format("zip compress: Error in compression:\n{}\nError code: {}\n",
                               e.what(), e.code().value());
      compressError = CompressError::FILE_READING_ERROR;
      std::cerr << std::format("zip compress: Error reading one file (collection.anki21b, "
                               "meta, media,..) of the apkg.\n");
      return false;
    }
  }

  if (ZIP_OK != zipClose(myZipFile, "anki zipped")) {
    compressError = CompressError::MINIZIP_ERROR;
    std::cout << std::format("zip compress: Error while closing the apkg.\n");
    return false;
  }
  return true;
}
} // namespace zip
} // namespace ankicpp
