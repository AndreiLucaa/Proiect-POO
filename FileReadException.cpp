//
// Created by Andrei Luca on 13.05.2025.
//

#include "FileReadException.h"

FileReadException::FileReadException(const std::string &filename): filename(filename) {}

const char * FileReadException::what() const noexcept {
    return ("Error reading file: " + filename).c_str();
}

const std::string & FileReadException::getFilename() const {
    return filename;
}
