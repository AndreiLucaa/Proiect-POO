//
// Created by Andrei Luca on 13.05.2025.
//

#include "InvalidCoordinatesException.h"

InvalidCoordinatesException::InvalidCoordinatesException(double latitude, double longitude): CountryException("Invalid coordinates: (" + std::to_string(latitude) + ", " + std::to_string(longitude) + ")") {}
