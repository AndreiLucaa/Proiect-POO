//
// Created by Andrei Luca on 13.05.2025.
//

#include "FileReadException.h"

FileReadException::FileReadException(const std::string &filename)
    : filename(filename), message("Error reading file: " + filename) {}

const char *FileReadException::what() const noexcept {
    return message.c_str();
}
// const std::string & FileReadException::getFilename() const {
//     return filename;
// }
