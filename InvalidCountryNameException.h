//
// Created by Andrei Luca on 13.05.2025.
//

#ifndef INVALIDCOUNTRYNAMEEXCEPTION_H
#define INVALIDCOUNTRYNAMEEXCEPTION_H
#include "CountryExceptions.h"


class InvalidCountryNameException : public CountryException {
public:
    explicit InvalidCountryNameException(const std::string &countryName)
        : CountryException("Invalid country name: " + countryName) {}
};


#endif //INVALIDCOUNTRYNAMEEXCEPTION_H
