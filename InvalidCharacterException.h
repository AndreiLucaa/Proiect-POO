//
// Created by Andrei Luca on 13.05.2025.
//

#ifndef INVALIDCHARACTEREXCEPTION_H
#define INVALIDCHARACTEREXCEPTION_H
#include "WordExceptions.h"


class InvalidCharacterException : public WordException {
public:
    explicit InvalidCharacterException(const std::string &msg);
};



#endif //INVALIDCHARACTEREXCEPTION_H
