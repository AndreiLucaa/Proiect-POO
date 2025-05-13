//
// Created by Andrei Luca on 13.05.2025.
//

#include "WordExceptions.h"

WordException::WordException(const std::string &msg): message(msg) {}

const char * WordException::what() const noexcept {
    return message.c_str();
}
