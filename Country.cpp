//
// Created by Andrei Luca on 15.04.2025.
//

#include "Country.h"
#include "CountryExceptions.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

#include "CountryNotFoundException.h"
#include "InvalidCoordinatesException.h"
#include "InvalidCountryNameException.h"

Country::Country(const std::string &name,
                 const std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string>> &validCountries,
                 double latitude, double longitude, const std::string &capital, long population, const std::string &currency)
    : name(name), validCountries(validCountries), latitude(latitude), longitude(longitude), capital(capital), population(population), currency(currency) {
    if (name.empty()) {
        throw InvalidCountryNameException(name);
    }
    if (latitude < -90.0 || latitude > 90.0 || longitude < -180.0 || longitude > 180.0) {
        throw InvalidCoordinatesException(latitude, longitude);
    }
    std::cout << "constructor Country\n";
}

void Country::displayHaversineResult(double /*lat1*/, double /*lon1*/, double /*lat2*/, double /*lon2*/) const {
    std::cout << "here the func from other class will be overridden" << std::endl;
}

std::string const& Country::getName() const {
    return name;
}

std::vector<std::tuple<std::string, std::pair<double, double>, std::string, int, std::string>> Country::
getValidCountries() const {
    return validCountries;
}

double Country::getLatitude() const {
    return latitude;
}

double Country::getLongitude() const {
    return longitude;
}

std::string Country::getCapital() const {
    return capital;
}

long Country::getPopulation() const {
    return population;
}

std::string Country::getCurrency() const {
    return currency;
}

bool Country::isValidCountry(const std::string &guess1) const {
    std::string upperGuess1 = guess1;
    std::transform(upperGuess1.begin(), upperGuess1.end(), upperGuess1.begin(), ::toupper);
    for (const auto &entry : validCountries) {
        std::string validCountryName = std::get<0>(entry);
        std::transform(validCountryName.begin(), validCountryName.end(), validCountryName.begin(), ::toupper);
        if (validCountryName == upperGuess1) {
            return true;
        }
    }
    return false;
}

bool Country::isCorrectCountry(const std::string &guess2) const {
    std::string upperGuess2 = guess2;
    std::transform(upperGuess2.begin(), upperGuess2.end(), upperGuess2.begin(), ::toupper);
    std::string upperName = name;
    std::transform(upperName.begin(), upperName.end(), upperName.begin(), ::toupper);
    return upperGuess2 == upperName;
}

std::pair<double, double> Country::getCoordinates(const std::string &guess3) const {
    std::string upperGuess3 = guess3;
    std::transform(upperGuess3.begin(), upperGuess3.end(), upperGuess3.begin(), ::toupper);
    for (const auto &entry : validCountries) {
        std::string validCountryName = std::get<0>(entry);
        std::transform(validCountryName.begin(), validCountryName.end(), validCountryName.begin(), ::toupper);
        if (validCountryName == upperGuess3) {
            return std::get<1>(entry);
        }
    }
    throw CountryNotFoundException(guess3);
}