//
// Created by Andrei Luca on 13.05.2025.
//

#ifndef INVALIDGUESSEXCEPTION_H
#define INVALIDGUESSEXCEPTION_H
#include "WordExceptions.h"


class InvalidGuessException : public WordException {
public:
    explicit InvalidGuessException(const std::string &msg);
};



#endif //INVALIDGUESSEXCEPTION_H
