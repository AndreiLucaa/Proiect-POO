//
// Created by Andrei Luca on 15.05.2025.
//

#ifndef INVALIDWORDLIST_H
#define INVALIDWORDLIST_H
#include "WordExceptions.h"


class InvalidWordList : public WordException{
public:
    explicit InvalidWordList(const std::string &msg);
};



#endif //INVALIDWORDLIST_H
