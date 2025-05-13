//
// Created by Andrei Luca on 13.05.2025.
//

#ifndef INVALIDCOORDINATESEXCEPTION_H
#define INVALIDCOORDINATESEXCEPTION_H
#include "CountryExceptions.h"


class InvalidCoordinatesException : public CountryException {
public:
    InvalidCoordinatesException(double latitude, double longitude)
        : CountryException("Invalid coordinates: (" + std::to_string(latitude) + ", " + std::to_string(longitude) + ")") {}
};


#endif //INVALIDCOORDINATESEXCEPTION_H
