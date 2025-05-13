//
// Created by Andrei Luca on 13.05.2025.
//

#ifndef INVALIDWORDLENGTHEXCEPTION_H
#define INVALIDWORDLENGTHEXCEPTION_H
#include "WordExceptions.h"


class InvalidWordLengthException : public WordException {
public:
    explicit InvalidWordLengthException(const std::string &msg);
};



#endif //INVALIDWORDLENGTHEXCEPTION_H
