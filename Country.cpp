//
// Created by Andrei Luca on 15.04.2025.
//

#include "Country.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include <utility>


Country::Country(const std::string &name,
    const std::vector<std::pair<std::string, std::pair<double, double>>> &validCountries, double latitude,
    double longitude): name(name), validCountries(validCountries), latitude(latitude), longitude(longitude) {
    std::cout << "constructor Country\n";
}

void Country::displayHaversineResult(double /*lat1*/, double /*lon1*/, double /*lat2*/, double /*lon2*/) const {
    std::cout << "here the func from other class will be overridden" << std::endl;
}

std::string const& Country::getName() const {
    return name;
}

std::vector<std::pair<std::string, std::pair<double, double>>> const& Country::getValidCountries() const {
    return validCountries;
}

double Country::getLatitude() const {
    return latitude;
}

double Country::getLongitude() const {
    return longitude;
}

bool Country::isValidCountry(const std::string &countryName) const {
    return std::any_of(validCountries.begin(), validCountries.end(),
                       [&countryName](const std::pair<std::string, std::pair<double, double>> &entry) {
                           return entry.first == countryName;
                       });
}
bool Country::isCorrectCountry(const std::string &guessCountry) const {
    return name == guessCountry;
}

std::pair<double, double> Country::getCoordinates(const std::string &countryName) const {
    auto it = std::find_if(validCountries.begin(), validCountries.end(),
                           [&countryName](const std::pair<std::string, std::pair<double, double>> &entry) {
                               return entry.first == countryName;
                           });
    if (it != validCountries.end()) {
        return it->second;
    }
    return {0.0, 0.0}; // Return default coordinates if the country is not found
}

// std::pair<double, double> Country::haversine(double lat1, double lon1, double lat2, double lon2) {
//     // Convert degrees to radians
//     lat1 *= DEG_TO_RAD;
//     lon1 *= DEG_TO_RAD;
//     lat2 *= DEG_TO_RAD;
//     lon2 *= DEG_TO_RAD;
//
//     // Haversine distance formula
//     double dlat = lat2 - lat1;
//     double dlon = lon2 - lon1;
//
//     double a = std::pow(std::sin(dlat / 2), 2) +
//                std::cos(lat1) * std::cos(lat2) *
//                std::pow(std::sin(dlon / 2), 2);
//
//     double c = 2 * std::asin(std::sqrt(a));
//     double distance = EARTH_RADIUS_KM * c;
//
//     // Bearing formula (initial heading)
//     double y = std::sin(dlon) * std::cos(lat2);
//     double x = std::cos(lat1) * std::sin(lat2) -
//                std::sin(lat1) * std::cos(lat2) * std::cos(dlon);
//     double bearing = std::atan2(y, x) * RAD_TO_DEG;
//
//     // Normalize bearing to 0-360
//     bearing = std::fmod((bearing + 360.0), 360.0);
//
//     return {distance, bearing};
// }
