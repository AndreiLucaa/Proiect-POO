//
// Created by Andrei Luca on 13.05.2025.
//

#include "CountryExceptions.h"

CountryException::CountryException(const std::string &message): message(message) {}

const char * CountryException::what() const noexcept {
    return message.c_str();
}
