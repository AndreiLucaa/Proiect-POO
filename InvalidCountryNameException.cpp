//
// Created by Andrei Luca on 13.05.2025.
//

#include "InvalidCountryNameException.h"

InvalidCountryNameException::InvalidCountryNameException(const std::string &countryName): CountryException("Invalid country name: " + countryName) {}
