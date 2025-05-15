//
// Created by Andrei Luca on 15.05.2025.
//

#include "InvalidWordList.h"

InvalidWordList::InvalidWordList(const std::string &msg): WordException("Invalid Word List: " + msg) {}
