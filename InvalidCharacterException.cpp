//
// Created by Andrei Luca on 13.05.2025.
//

#include "InvalidCharacterException.h"

InvalidCharacterException::InvalidCharacterException(const std::string &msg): WordException("Invalid Character: " + msg) {}
