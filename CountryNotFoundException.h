//
// Created by Andrei Luca on 13.05.2025.
//

#ifndef COUNTRYNOTFOUNDEXCEPTION_H
#define COUNTRYNOTFOUNDEXCEPTION_H
#include "CountryExceptions.h"


class CountryNotFoundException : public CountryException {
public:
    explicit CountryNotFoundException(const std::string &countryName)
        : CountryException("Country not found: " + countryName) {}
};


#endif //COUNTRYNOTFOUNDEXCEPTION_H
