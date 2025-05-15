//
// Created by Andrei Luca on 13.05.2025.
//

#include "CountryNotFoundException.h"

CountryNotFoundException::CountryNotFoundException(const std::string &countryName): CountryException("Country not found: " + countryName) {}
