//
// Created by Andrei Luca on 13.05.2025.
//

#include "InvalidWordLengthException.h"

InvalidWordLengthException::InvalidWordLengthException(const std::string &msg): WordException("Invalid Word Length: " + msg) {}
