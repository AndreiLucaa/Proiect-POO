//
// Created by Andrei Luca on 13.05.2025.
//

#include "InvalidGuessException.h"

InvalidGuessException::InvalidGuessException(const std::string &msg): WordException("Invalid Guess: " + msg) {}
